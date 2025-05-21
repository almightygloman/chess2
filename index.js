import express from "express";
import { createServer } from 'node:http';
import { dirname, join } from "node:path";
import { fileURLToPath } from "node:url";
import { Server } from "socket.io";
import { spawn } from 'node:child_process';

const app = express();
const server = createServer(app);
const io = new Server(server);
const __dirname = dirname(fileURLToPath(import.meta.url));

// Spawn the chess engine as a child process
const chessEngine = spawn('./engine/main');
let currentFen = '';

// Handle data coming from the chess engine
chessEngine.stdout.on('data', (data) => {
  const output = data.toString().trim();
  
  // Check if this is a FEN update
  if (output.startsWith('FEN:')) {
    currentFen = output.substring(4); // Remove the 'FEN:' prefix
    console.log('New board state:', currentFen);
    
    // Broadcast the new board state to all connected clients
    io.emit('fen_update', currentFen);
  }
});

// Handle chess engine errors
chessEngine.stderr.on('data', (data) => {
  console.error('Chess engine error:', data.toString());
});

// Handle chess engine exit
chessEngine.on('close', (code) => {
  console.log(`Chess engine process exited with code ${code}`);
});

// Express route for the main page
app.get('/', (req, res) => {
  res.sendFile(join(__dirname, 'index.html'));
});

// Socket.IO connection handling
io.on('connection', (socket) => {
  console.log('A user connected');
  
  // Send current board state to new clients
  if (currentFen) {
    socket.emit('fen_update', currentFen);
  }
  
  // Listen for move requests from clients
  socket.on('make_move', (moveData) => {
    if (moveData && moveData.from !== undefined && moveData.to !== undefined) {
      const command = `move ${moveData.from} ${moveData.to}\n`;
      chessEngine.stdin.write(command);
    }
  });
  
  // Normal chat message handling
  socket.on('message', (msg) => {
    io.emit('message', msg);
  });
  
  socket.on('disconnect', () => {
    console.log('A user disconnected');
  });
});

// Start the server
server.listen(3000, '0.0.0.0', () => { 
  console.log('Server running and accessible on network at http://localhost:3000');
});

// Properly clean up the chess engine process when Node.js exits
process.on('exit', () => {
  chessEngine.stdin.write('quit\n');
  chessEngine.kill();
});

// Handle unexpected terminations
['SIGINT', 'SIGTERM', 'SIGQUIT'].forEach(signal => {
  process.on(signal, () => {
    chessEngine.stdin.write('quit\n');
    chessEngine.kill();
    process.exit();
  });
});