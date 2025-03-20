import pprint
import sys
import time

import numpy as np
import scipy.signal as signal
from scipy.signal import lfilter
from ifxradarsdk import get_version
from ifxradarsdk.fmcw import DeviceFmcw
from ifxradarsdk.fmcw.types import (
    create_dict_from_sequence,
    FmcwSimpleSequenceConfig,
    FmcwSequenceChirp,
)

# Device settings specific to BGT60UTR11AIP
num_rx_antennas = 1  # The sensor has one receiver antenna.
frame_rate = 20      # Hz (sampling rate)
number_of_chirps = 1
samples_per_chirp = 64

# Define constants
processing_window_time = 20  # seconds
buffer_time = 5 * processing_window_time  # seconds (unused here)
buffer_data_size = int(buffer_time * frame_rate)
processing_data_size = int(processing_window_time * frame_rate)
fft_size_range_profile = samples_per_chirp * 2

# Vital sign processing parameters
low_breathing = 0.15
high_breathing = 0.6
low_heart = 0.85
high_heart = 2.4
nyquist_freq = 0.5 * frame_rate
filter_order = frame_rate + 1
breathing_b = signal.firwin(
    filter_order, [low_breathing / nyquist_freq, high_breathing / nyquist_freq], pass_zero=False
)
heart_b = signal.firwin(
    filter_order, [low_heart / nyquist_freq, high_heart / nyquist_freq], pass_zero=False
)

# Additional parameters for vital sign FFT analysis
vital_signs_sample_rate = frame_rate
fft_size_vital_signs = processing_data_size * 4
index_start_breathing = 0
index_end_breathing = fft_size_vital_signs
index_start_heart = 0
index_end_heart = fft_size_vital_signs

# Range selection parameters (in meters)
object_distance_start_range = 0.5
object_distance_stop_range = 0.6

class RadarDataProcessor:
    def calc_range_fft(self, frame):
        """
        Compute the range FFT for one acquired frame.
        The frame is expected to have shape
          (num_rx_antennas, num_chirps, num_samples_per_chirp)
        """
        _, num_chirps_per_frame, num_samples_per_chirp = np.shape(frame)
        range_fft_antennas_buffer = np.zeros(int(fft_size_range_profile / 2), dtype=np.complex128)

        for iAnt in range(num_rx_antennas):
            mat = frame[iAnt, :, :]
            # Remove DC offset for each chirp
            avgs = np.average(mat, axis=1).reshape(num_chirps_per_frame, 1)
            mat = mat - avgs
            # Apply windowing function
            window = signal.windows.blackmanharris(num_samples_per_chirp).reshape(1, num_samples_per_chirp)
            mat *= window
            # Zero-pad the signal to the required FFT length
            zp1 = np.pad(mat, ((0, 0), (0, fft_size_range_profile - num_samples_per_chirp)), 'constant')
            # Compute FFT for each chirp
            range_fft = np.fft.fft(zp1, fft_size_range_profile) / num_samples_per_chirp
            range_fft = 2 * range_fft[:, : int(fft_size_range_profile / 2)]
            temp_range_fft = np.sum(range_fft, axis=0)
            range_fft_antennas_buffer += temp_range_fft

        return range_fft_antennas_buffer / num_rx_antennas

    def process_frame(self, frame, max_range):
        """
        Processes a single frame: computes the range FFT,
        extracts a target range bin, obtains the phase signal,
        performs filtering and FFT analysis to estimate breathing
        and heart rates.
        """
        range_fft = self.calc_range_fft(frame)
        if range_fft is not None:
            # Compute magnitude of range FFT
            range_fft_abs = np.abs(range_fft)
            # Range bin selection based on the provided distance
            start_index_range = int(
                object_distance_start_range / max_range * (fft_size_range_profile / 2)
            )
            stop_index_range = int(
                object_distance_stop_range / max_range * (fft_size_range_profile / 2)
            )
            range_profile_peak_index = (
                np.argmax(range_fft_abs[start_index_range:stop_index_range])
                + start_index_range
            )
            # Extract the phase signal from the selected range bin
            selected_bin_data = range_fft[range_profile_peak_index]
            wrapped_phase = np.angle(selected_bin_data)
            # Unwrap phase to remove discontinuities
            unwrapped_phase = np.unwrap(wrapped_phase)
            # Band-pass filter the unwrapped phase for breathing and heart rate signals
            filtered_breathing = lfilter(breathing_b, 1, unwrapped_phase)
            filtered_heart = lfilter(heart_b, 1, unwrapped_phase)
            # FFT analysis of the filtered signals
            breathing_fft = np.abs(np.fft.fft(filtered_breathing, n=fft_size_vital_signs))
            heart_fft = np.abs(np.fft.fft(filtered_heart, n=fft_size_vital_signs))
            # Estimate peaks in the FFT spectrum
            breathing_peak_index = (
                np.argmax(breathing_fft[index_start_breathing:index_end_breathing])
                + index_start_breathing
            )
            breathing_rate_hz = breathing_peak_index * vital_signs_sample_rate / fft_size_vital_signs
            heart_peak_index = (
                np.argmax(heart_fft[index_start_heart:index_end_heart])
                + index_start_heart
            )
            heart_rate_hz = heart_peak_index * vital_signs_sample_rate / fft_size_vital_signs
            # Convert frequency to beats per minute (bpm)
            breathing_rate_bpm = breathing_rate_hz * 60
            heart_rate_bpm = heart_rate_hz * 60

            print(f"Estimated Breathing Rate: {breathing_rate_bpm:.2f} bpm")
            print(f"Estimated Heart Rate: {heart_rate_bpm:.2f} bpm")

if __name__ == "__main__":
    with DeviceFmcw() as device:
        print("Radar SDK Version: " + get_version())
        print("UUID of board: " + device.get_board_uuid())
        print("Sensor: " + str(device.get_sensor_type()))

        rx_mask = {1: 1}.get(num_rx_antennas, 1)

        config = FmcwSimpleSequenceConfig(
            frame_repetition_time_s=1 / frame_rate,
            chirp_repetition_time_s=0.001,
            num_chirps=number_of_chirps,
            tdm_mimo=False,
            chirp=FmcwSequenceChirp(
                start_frequency_Hz=57_400_000_000,
                end_frequency_Hz=63_000_000_000,
                sample_rate_Hz=4e6,
                num_samples=samples_per_chirp,
                rx_mask=rx_mask,
                tx_mask=1,
                tx_power_level=31,
                lp_cutoff_Hz=500000,
                hp_cutoff_Hz=80000,
                if_gain_dB=33,
            ),
        )
        sequence = device.create_simple_sequence(config)
        device.set_acquisition_sequence(sequence)

        pp = pprint.PrettyPrinter()
        pp.pprint(create_dict_from_sequence(sequence))

        # Calculate range resolution and max_range based on sensor configuration
        range_res = 3e8 / (2 * device.get_chirp_sampling_bandwidth(config.chirp))
        print("Range resolution =", range_res * 2)
        max_range = range_res * samples_per_chirp / 2
        print("Maximum range =", max_range)

        radar_processor = RadarDataProcessor()

        # Main processing loop without multithreading
        while True:
            frame_contents = device.get_next_frame()
            # Process each frame immediately
            for frame in frame_contents:
                radar_processor.process_frame(frame, max_range)
            # Short delay to alleviate CPU usage
            time.sleep(0.001)
