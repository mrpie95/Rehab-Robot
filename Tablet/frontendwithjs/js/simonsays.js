$(document).ready(function(){
	//reset input fields on page refresh
	document.getElementById("bendKnees").checked = false;
	document.getElementById("raiseRightArm").checked = false;
	document.getElementById("raiseLeftLeg").checked = false;
	
	document.getElementById("1min").checked = false;
	document.getElementById("2mins").checked = false;
	document.getElementById("5mins").checked = false;
	
	

	$(document.getElementById("therapy")).click(function() {
		window.location.href = "therapy.html";
	});
	
	$(document.getElementById("games")).click(function() {
		window.location.href = "games.html";
	});
	
	$(document.getElementById("support")).click(function() {
		window.location.href = "support.html";
	});
	
	//click handler for start button
	$(document.getElementById("start")).click(startGame);
	
});

function startGame() {
	var moves = "";
	var duration = "";
	
	//Get moves
	if (document.getElementById("bendKnees").checked == true) {
		moves += "bendKnees";
	}
	
	if (document.getElementById("raiseRightArm").checked == true) {
		//add comma or other separator
		if (moves != "") {
			moves += ",";
		}
		moves += "raiseRightArm";
	}
	
	if (document.getElementById("raiseLeftLeg").checked == true) {
		//add comma or other separator
		if (moves != "") {
			moves += ",";
		}
		moves += "raiseLeftLeg";
	}
	
	//Get duration
	if (document.getElementById("1min").checked == true) {
		duration = "1min";
	}
	else if (document.getElementById("2mins").checked == true) {
		duration = "2mins";
	}
	else if (document.getElementById("5mins").checked == true) {
		duration = "5mins";
	}
	
	//test alert to trigger start of game
	if (moves == "") {
		alert("Please select moves!");
	} 
	else if (duration == "") {
		alert("Please select duration!");
	}
	else {
		alert("Game started with moves: " + moves + " Duration: " + duration);
		//TODO: Insert code here that will send these values to the server
	}	
}