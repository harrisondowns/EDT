var studentNote = "";
var teacherNote = "";
var express = require('express');
var app = express();
var port = process.env.PORT || 8080;
var bodyParser = require('body-parser');
app.use(bodyParser.json()); // support json encoded bodies
app.use(bodyParser.urlencoded({ extended: true })); // support encoded bodies

app.get('/getStudent', function(req, res) {
  res.send(studentNote);
});

app.post('/studentPut', function(req, res) {
    studentNote = req.body.note;
    res.send(200);
});

app.get('/getTeacher', function(req, res) {
  res.send(teacherNote);
});

app.post('/teacherPut', function(req, res) {
    teacherNote = req.body.note;
    res.send(200);
});

var answer = "";

app.get('/getAnswer', function(req, res) {
    res.send(answer);
});

app.post('/setAnswer', function(req, res) {
    answer = req.body.answer;
    res.send(200);
});
	
app.get('/getTime', function(req, res) {
    var dt = new Date();

    dt.setTime(dt.getTime() + dt.getTimezoneOffset() * 60 * 1000);
    
    var offset = -60 * 4;
    var date = new Date(dt.getTime() + offset * 60 * 1000);
    
    var hour = date.getHours();
    hour = (hour < 10 ? "0" : "") + hour;

    var min  = date.getMinutes();
    min = (min < 10 ? "0" : "") + min;

    res.send(hour+":"+min);
});

app.listen(port);

