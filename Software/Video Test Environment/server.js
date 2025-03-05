// Node.js packages
const express = require('express');
const http = require('http');
const socketIo = require('socket.io');
// Creates connections between different devices
const cors = require('cors');

// Initialize the express app and server
const app = express();
const server = http.createServer(app);

// Initialize socket.io on the server
const io = socketIo(server, {
  cors: {
    origin: "http://localhost", // Allow only localhost for testing
    methods: ["GET", "POST"]
  }
});

// CORS for cross-device communication
app.use(cors());

// Frontend files for public folder
app.use(express.static('public'));

// Listens for incoming and outgoing connections
io.on('connection', (socket) => {
  console.log('A user connected:', socket.id);

  // Backend WebRTC with Console testing

  // Send the WebRTC offer to the client and only broadcast to client
  socket.on('offer', (offer) => {
    console.log('Received offer from:', socket.id);
    socket.broadcast.emit('offer', offer);
  });

  // Send the WebRTC answer from the client to the sender
  socket.on('answer', (answer) => {
    console.log('Received answer from:', socket.id);
    socket.broadcast.emit('answer', answer);
  });

  // ICE candidates (MDN Web Docs API info)
  socket.on('ice-candidate', (candidate) => {
    console.log('Received ICE candidate from:', socket.id);
    socket.broadcast.emit('ice-candidate', candidate);
  });

  // disconnections
  socket.on('disconnect', () => {
    console.log('A user disconnected:', socket.id);
  });
});

// Start the server on localhost
const PORT = 3000;
server.listen(PORT, () => {
  console.log(`Server running on http://localhost:${PORT}`);
});
