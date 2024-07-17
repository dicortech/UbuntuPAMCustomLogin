
// server.js File 
const express = require('express'); // Importing express module 
var bodyParser = require("body-parser");
  
const app = express(); // Creating an express object 
app.use(bodyParser.urlencoded({extended : true}));
app.use(bodyParser.urlencoded({
  extended: true
}));
app.use(bodyParser.json());
  
const port = 8000;  // Setting an port for this application 
  
  
// Starting server using listen function 
app.listen(port, function (err) { 
   if(err){ 
       console.log("Error while starting server"); 
   } 
   else{ 
       console.log("Server has been started at "+port); 
   } 
}) 

app.get('/', function (req, res) {
  res.send('get - in');
})

app.post('/verify', function (req, res) {
    var pass = req.body.pass;
    var now = new Date();
    console.log(now.toString()+" :- Password verfication request received: "+pass);
    var user = "";
    if(pass == "123456") user = "user1";
    else if(pass == "234567") user = "user2"; 
    else if(pass == "345678") user = "user3"; 
  
    if(user != "") {
	console.log(now.toString()+" :- Password verfied for user: "+user);
	res.status(200).send({"user":user});
    }
    else {
	console.log(now.toString()+" :- Password verfication failed!! ");
	res.status(400).send({"user":"error"});
    }
})
