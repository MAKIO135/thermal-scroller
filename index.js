const { SerialPort } = require('serialport')
const express = require('express')
const app = express()
const http = require('http').Server(app)
const io = require('socket.io')(http)

let port
let isSerialOpen = false
SerialPort.list().then(r => {
    let path = r.filter(d => d.manufacturer.includes('Arduino'))[0].path // uses first serialPort which is an Arduino
    if(path) {
        port = new SerialPort({ path, baudRate: 9600 })
        port.on('open', () => isSerialOpen = true)
    }
})

http.listen(8000, () => console.log('http://localhost:8000/'))
app.use(express.static(__dirname + '/public'))
app.get('/', (req, res) => res.sendFile('index.html'))

io.on('connection' , socket => {
    socket.on('scroll', data => {
        console.log(data)
        if(isSerialOpen) port.write(`${data}`)
	})
})
