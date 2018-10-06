$(document).ready(function(){
	//reset input fields on page refresh
	$(document.getElementById("exampleInputEmail1").value = "");
	$(document.getElementById("exampleInputPassword1").value = "");

	//click handler for login button
	$(document.getElementById("login")).click(validate);
});

function validate() {
	//get input field values
	var username = document.getElementById("exampleInputEmail1").value;
	var password = document.getElementById("exampleInputPassword1").value;
	
	if (username == "") {
		alert("Please enter username!");
	}
	if (password == "") {
		alert("Please enter password!");
	}
	
	//TODO: Insert code here that will check with database if username/password is valid
	
	//If username/password is valid:
	if (username != "" && password != "") {
		window.location.href = "Games.html";
	}
}
