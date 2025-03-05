// Connect to the signaling server using socket.io
const socket = io();

// Create WebRTC PeerConnection with STUN servers
const peerConnection = new RTCPeerConnection({
  iceServers: [
    { urls: 'stun:stun.l.google.com:19302' }, //Look into setting up own STUN Server
    { urls: 'stun:stun1.l.google.com:19302' } 
  ]
});

// Get video elements
const localVideo = document.getElementById('localVideo');

// Request access to user's webcam
navigator.mediaDevices.getUserMedia({ video: true, audio: false })
  .then((stream) => {
    console.log('Local camera stream obtained', stream);
    localVideo.srcObject = stream;

    // Add local stream to peer connection
    stream.getTracks().forEach((track) => {
      console.log('Adding track:', track);
      peerConnection.addTrack(track, stream);
    });
  })
  .catch((error) => {
    console.error('Error accessing camera:', error);
  });

// Handle ICE candidates
peerConnection.onicecandidate = (event) => {
  if (event.candidate) {
    console.log('Sending ICE candidate:', event.candidate);
    socket.emit('ice-candidate', event.candidate);
  }
};

// Handle offer from the signaling server
socket.on('offer', async (offer) => {
  console.log('Received WebRTC offer:', offer);
  await peerConnection.setRemoteDescription(new RTCSessionDescription(offer));
  const answer = await peerConnection.createAnswer();
  await peerConnection.setLocalDescription(answer);
  socket.emit('answer', answer);
});

// Handle answer from the signaling server
socket.on('answer', async (answer) => {
  console.log('Received WebRTC answer:', answer);
  await peerConnection.setRemoteDescription(new RTCSessionDescription(answer));
});

// Handle ICE candidates from the signaling server
socket.on('ice-candidate', async (candidate) => {
  console.log('Received ICE candidate:', candidate);
  await peerConnection.addIceCandidate(new RTCIceCandidate(candidate));
});

// Debugging connection state
peerConnection.onconnectionstatechange = () => {
  console.log('Connection state:', peerConnection.connectionState);
};

peerConnection.oniceconnectionstatechange = () => {
  console.log('ICE state:', peerConnection.iceConnectionState);
};

// Function to initiate WebRTC connection
async function startWebRTC() {
  try {
    const offer = await peerConnection.createOffer();
    await peerConnection.setLocalDescription(offer);
    socket.emit('offer', offer);
  } catch (error) {
    console.error('Error creating WebRTC offer:', error);
  }
}

// Start WebRTC
startWebRTC();