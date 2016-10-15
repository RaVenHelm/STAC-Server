const net = require('net');

const client = net.createConnection({port: 1025}, () => {
  //'connect' listener
  console.log('connected to server!');
  client.write("LOGA \"jsmith\" \"password1\" \"John\" \"Smith\"");
});

client.on('data', data => {
  console.log(data.toString());
  // client.end();
});

client.on('end', () => {
  console.log('disconnected from server');
});
