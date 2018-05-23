var accessToken = "09774994a7a3472fa046ae4724745d32";
		var baseUrl = "https://api.api.ai/v1/";
		  
		<!-- -->
		var transcript = ["This is a transcript"];
		<!-- -->
		
		$(document).ready(function() {
			$("#input").keypress(function(event) {
				if (event.which == 13) {
					event.preventDefault();
					send();
				}
			}); 
			$("#rec").click(function(event) {
				switchRecognition();
			});
		});
		var recognition;
		function startRecognition() {
			recognition = new webkitSpeechRecognition();
			recognition.onstart = function(event) {
				updateRec();
			};
			recognition.onresult = function(event) {
				var text = "";
			    for (var i = event.resultIndex; i < event.results.length; ++i) {
			    	text += event.results[i][0].transcript;
			    }
			    setInput(text);
				stopRecognition();
			};
			recognition.onend = function() {
				stopRecognition();
			};
			recognition.lang = "en-US";
			recognition.start();
		}
	
		function stopRecognition() {
			if (recognition) {
				recognition.stop();
				recognition = null;
			}
			updateRec();
		}
		function switchRecognition() {
			if (recognition) {
				stopRecognition();
			} else {
				startRecognition();
			}
		}
		function setInput(text) {
			$("#input").val(text); 
			send();
		}
		function updateRec() {
			$("#rec").text(recognition ? "Stop" : "Speak");
		}
		function send() {
			var text = $("#input").val();
			setResponse("You : " + text);
			$.ajax({
				type: "POST",
				url: baseUrl + "query?v=20150910",
				contentType: "application/json; charset=utf-8",
				dataType: "json",
				headers: {
					"Authorization": "Bearer " + accessToken
				},
				data: JSON.stringify({ query: text, lang: "en", sessionId: "somerandomthing" }),
				success: function(data) {
					setResponse("TrashTalk : " + data.result.fulfillment.speech); // Add 
				},
				error: function() {
					setResponse("Internal Server Error");
				}
			}); 
			setResponse("Loading...");
		}
		function setResponse(val) {
			$("#response").text(val);
			
			 if(val == "Loading...")
			{}
			else
			transcript.push(val); <!-- -->
			
			speak(val);
			
			
			
				
		}
		
		function speak(string){
var utterance = new SpeechSynthesisUtterance();
utterance.voice = speechSynthesis.getVoices().filter(function(voice){return voice.name == "Junior";})[0];
utterance.text = string;
utterance.lang = "en-US";
utterance.volume = 1; //0-1 interval
utterance.rate = 1;
utterance.pitch = 2; //0-2 interval
speechSynthesis.speak(utterance);
} 