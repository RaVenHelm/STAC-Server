const net = require('net');

const client = net.createConnection({port: 1025}, () => {
  //'connect' listener
  console.log('connected to server!');
  client.write(`LOGA "ejohn" "rocketman"`);
  //client.write("CRCR \"A Venture\" \"UNC-2\" \"11-09-2016\" \"03-14-2017\" \"\" \"M1030-1130;W1030-1130;F1030-1130\"");
  // setTimeout(() => {client.write("CSRC \"Mr Jones and Me\" \"UNC-2\"")}, 1000);
  setTimeout(() => { client.write(`CSRC "" "UNC-2"`); }, 2000);
  // setTimeout(() => { client.write("LOGO"); }, 3000);
});

client.on('data', data => {
  const msg = data.toString().trim();
  console.log(`Server response: ${msg}`);
  console.log(`Response length: ${msg.length}`);

  const searchRes = 'CSRR S';
  if(msg.startsWith(searchRes)) {
    const ids_str = msg.slice(searchRes.length + 1);
    console.log(`Class IDs: ${ids_str}`);
    const ids = ids_str.split(' ');

    ids.forEach(id => {
      const cdtl = `CDTL ${id}`;
      console.log(`Sending message: ${cdtl}`);
      client.write(cdtl);
    });
    client.write("LOGO");
  }
});

client.on('end', () => {
  console.log('disconnected from server');
});
