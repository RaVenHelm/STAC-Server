const net = require('net');

const client = net.createConnection({port: 1025}, () => {
  //'connect' listener
  console.log('connected to server!');
  client.write("LOGA \"ejohn\" \"rocketman\"");
  // client.write("CRCR \"The White Album\" \"UNC-2\" \"11-09-2016\" \"03-14-2017\" \"\" \"M1030-1130;W1030-1130;F1030-1130\"");
  client.write("CSRC \"The White Album\" \"UNC-2\"");
});

client.on('data', data => {
  console.log(data.toString());
});

client.on('end', () => {
  console.log('disconnected from server');
});
