import express from "express";
import { Socket } from "node:dgram";
import { createServer } from 'node:http';
import { dirname, join } from "node:path";
import { fileURLToPath } from "node:url";
import { Server } from "socket.io";

const app = express();
const server = createServer(app);
const io = new Server(server);

const __dirname = dirname(fileURLToPath(import.meta.url));

app.get('/', (req,res) => {
    res.sendFile(join(__dirname, 'index.html'));
});

io.on('connection', (socket) => {
    socket.on('message', (msg)=>{
        io.emit('message', msg);
    });
    
});

server.listen(3000, '0.0.0.0', () => { 
  console.log('server running and accessible on network');
});