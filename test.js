const net = require('net');

const client = net.createConnection({port: 1025}, () => {
  //'connect' listener
  console.log('connected to server!');
  client.write("LOGU \"ejohn\" \"rocketman\"");
  setTimeout(() => client.write("LOGU \"ejohn\" \"rocketman\""), 3000);
});

client.on('data', data => {
  console.log(data.toString());
});

client.on('end', () => {
  console.log('disconnected from server');
});
