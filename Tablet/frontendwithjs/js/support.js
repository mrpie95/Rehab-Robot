$(document).ready(function(){
	/*
	//Therapy not accessible
	$(document.getElementById("therapy")).click(function() {
		window.location.href = "Therapy.html";
	});
	*/
	
	$(document.getElementById("games")).click(function() {
		window.location.href = "Games.html";
	});
	
	$(document.getElementById("support")).click(function() {
		window.location.href = "Support.html";
	});
	
	//guide buttons	
	$(document.getElementById("userguide")).click(function() {
		alert("User Guide (TODO: this will open userguide.pdf)");
	});
	
	$(document.getElementById("technicalguide")).click(function() {
		alert("Technical Guide (TODO: this will open technicalguide.pdf)");
	});
});
