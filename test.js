const net = require('net');

const client = net.createConnection({port: 1025}, () => {
  //'connect' listener
  console.log('connected to server!');
  client.write("LOGU \"ejohn\" \"rocketman\"");
  setTimeout(() => client.write("REGU \"rsolomon\" \"highcommander\" \"Dick\" \"Solomon\""), 1000);
  setTimeout(() => client.write("LOGO"), 3000);
});

client.on('data', data => {
  console.log(data.toString());
  // setTimeout(() => client.end(), 3000);
});

client.on('end', () => {
  console.log('disconnected from server');
});
