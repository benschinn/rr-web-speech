type voice;
type speech = {
 .
   [@bs.set] "rate": float,
   [@bs.set] "voice": voice,
}
type t = {
  .
    [@bs.meth] "getVoices": unit => array(voice),
};

[@bs.val] [@bs.scope ("window")] external speechSynthesis: t  = "";
[@bs.new] external speechSynthesisUtterance: string => speech = "SpeechSynthesisUtterance";

let synth = speechSynthesis;

let voices = synth##getVoices();

let utterThis = speechSynthesisUtterance("hi");

utterThis##rate #= 1.5;

utterThis##voice #= voices[28];
