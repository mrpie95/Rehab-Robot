$(document).ready(function(){
	$(document.getElementById("therapy")).click(function() {
		window.location.href = "therapy.html";
	});
	
	$(document.getElementById("games")).click(function() {
		window.location.href = "games.html";
	});
	
	$(document.getElementById("support")).click(function() {
		window.location.href = "support.html";
	});
	
	//guide buttons	
	$(document.getElementById("userguide")).click(function() {
		alert("User Guide (TODO: this will open userguide.pdf)");
	});
	
	$(document.getElementById("technicalguide")).click(function() {
		alert("Technical Guide (TODO: this will open technicalguide.pdf)");
	});
});
