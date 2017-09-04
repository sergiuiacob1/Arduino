var repeater;
var xVal, yVal;
var axis3, axis0;
var speedInterval = 50; //send values each speedInterval seconds

function init() {
	getAxis();
	createSaveButton();
}

function importScript(url) {
	var imported = document.createElement('script');
	imported.src = url;
	document.head.appendChild(imported);
}

function getAxis() {
	var list = document.getElementsByClassName("axes")[0];
	axis3 = list.getElementsByClassName("ng-scope")[3];
	axis0 = list.getElementsByClassName("ng-scope")[0];
}

function getJoystickVals() {
	yVal = axis3.getElementsByClassName("ng-binding")[1].innerHTML;
	xVal = axis0.getElementsByClassName("ng-binding")[1].innerHTML;

	//console.log (yVal);
	//console.log (xVal);
	sendValues((xVal * 10000) | 0, (-yVal * 10000) | 0);
	repeater = setTimeout(getJoystickVals, speedInterval);
}

function sendValues(xVal, yVal) {
	download(xVal + " " + yVal + "\0", 'joystickVals.txt', 'text/plain');
	document.getElementById("valDownload").click();
}

function createSaveButton() {
	var div = document.createElement('div');
	div.setAttribute('id', 'divButton');
	div.innerHTML = "<a href='' id ='valDownload' >valDownload</a>";
	document.body.appendChild(div);
}

function download(text, name, type) {
	var a = document.getElementById("valDownload");
	var file = new Blob([text], { type: type });
	a.href = URL.createObjectURL(file);
	a.download = name;
}

init();
getJoystickVals();
