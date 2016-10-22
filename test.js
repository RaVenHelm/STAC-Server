const net = require('net');

const client = net.createConnection({port: 1025}, () => {
  //'connect' listener
  console.log('connected to server!');
  client.write("LOGU \"ejohn\" \"rocketman\"");
  client.write("LOGU \"rsolomon\" \"highcommander\"");
  setTimeout(() => client.write("LOGO"), 3000);
});

client.on('data', data => {
  console.log(data.toString());
});

client.on('end', () => {
  console.log('disconnected from server');
});
