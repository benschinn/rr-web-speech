type event;

type t = {
  .
    [@bs.meth] "start": unit => unit,
    [@bs.set]  "onresult": event, 
}; 

type sgl = { . [@bs.meth] "addFromString": (string, int) => unit };

[@bs.val] external webkitSpeechRecognition : t = "webkitSpeechRecognition";
[@bs.new] external speechRecognition : t = "SpeechRecognition";
[@bs.new] external speechGrammarList : sgl = "SpeechGrammarList";

[%%raw "var SpeechRecognition = SpeechRecognition || webkitSpeechRecognition"];
[%%raw "var SpeechRecognition = SpeechRecognition"];
[%%raw "var SpeechGrammarList = SpeechGrammarList || webkitSpeechGrammarList"];
[%%raw "var SpeechRecognitionEvent = SpeechRecognitionEvent || webkitSpeechRecognitionEvent"];

let recognition = speechRecognition;
let speechRecognitionList = speechGrammarList;


