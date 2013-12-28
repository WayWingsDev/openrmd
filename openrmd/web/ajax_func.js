function getXMLHTTPRequest()
{
	var req = false;

	try {
		/* for Firefox */
		req = new XMLHttpRequest();
	} catch (err) {
		try {
			/* for some versions of IE */
			req = new ActiveXObject("Msxml2.XMLHTTP");
		} catch (err) {
			try {
				/* for some other versions of IE */
				req = new ActiveXObject("Microsoft.XMLHTTP");
			} catch(err) {
				req = false;
			}
		}
	}

	return req;
}

function ajaxFunc(callback, cgi)
{
	req = getXMLHTTPRequest();

	if (req) {
		req.onreadystatechange = callback;
		myRand = parseInt(Math.random() * 9999999999999);
		req.open("GET", cgi+"?rand="+myRand);
		req.send(null);
	}
}

function ajaxCallback()
{
	if (req.readyState != 4)
		return;

	if (req.status == 200)
		return req.responseText;
}

function getProcessState() 
{
	ajaxFunc(processStateCallback, "cgi-bin/process_state.cgi");
}

function deviceCfg() 
{
	ajaxFunc(deviceCfgCallback, "cgi-bin/device_config.cgi");
}

function processStateCallback()
{
	var ret = ajaxCallback();
	var imgsrc = document.getElementById("openrmd_state");

	if (ret == "RUNNING") {
		document.getElementById("state").innerHTML = "<h3>RUNNING</h3>";
		imgsrc.src="RUNNING.jpg";
	} else {
		document.getElementById("state").innerHTML = "<h3>STOP</h3>"; 
		imgsrc.src="STOP.jpg";
	}
}

function deviceCfgCallback()
{
	var ret = ajaxCallback();

	if (ret == null || ret.length <= 0)
		return;
	document.getElementById("cameras").innerHTML = ret;
}
