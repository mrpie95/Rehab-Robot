$(document).ready(function(){
	//reset input fields on page refresh
	$(document.getElementById("username").value = "");
	$(document.getElementById("password").value = "");
	
	//click handler for login button
	$(document.getElementById("login")).click(validate);
});

function validate() {
	//get input field values
	var username = document.getElementById("username").value;
	var password = document.getElementById("password").value;
	
	if (username == "") {
		alert("Please enter username!");
	}
	if (password == "") {
		alert("Please enter password!");
	}
	
	//TODO: Insert code here that will check with database if username/password is valid
	
	//If username/password is valid:
	if (username != "" && password != "") {
		window.location.href = "landing.html";
	}
}