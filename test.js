const net = require('net');

const client = net.createConnection({port: 1025}, () => {
  //'connect' listener
  console.log('connected to server!');
  client.write(JSON.stringify({host: '192.168.20.10', data: 'Heartbeat'}));
});

client.on('data', data => {
  console.log(data.toString());
  // client.end();
});

client.on('end', () => {
  console.log('disconnected from server');
});
