const config = require('./config.json') //config.json file
const { SerialPort } = require('serialport')
const express = require('express')
const app = express()
const http = require('http').Server(app)
const io = require('socket.io')(http)

let isSerialOpen = false
const port = new SerialPort({ path: config.serialPort, baudRate: config.serialRate })
port.on('open', () => {
    console.log(config.serialPort + ' open');
    isSerialOpen = true
})

// http://localhost:8000/
http.listen(config.serverPort, () => console.log('listening on', config.serverPort))
app.use(express.static(__dirname + '/public'))
app.get('/', (req, res) => res.sendFile('index.html'))

io.on('connection' , socket => {
    socket.on('scroll', data => {
        console.log(data)
        if(isSerialOpen) port.write(`${data}`)
	})
})
