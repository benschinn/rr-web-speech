type action =
  | SetSpeechResult(string);

type state = {
  speechResult: string,
};

let recognition = WebSpeechAPI.recognition;
let grammar = "#JSGF V1.0; grammar colors; public <words> =";

WebSpeechAPI.speechRecognitionList##addFromString(grammar, 1);

let handleClick = (_event, dispatch) => {
  Js.log("listening...");
  recognition##start();
  recognition##onresult #= [%raw {|
    (event) => 
      Curry._1(dispatch, /* SetSpeechResult */[event.results[event.results.length - 1][0].transcript])
  |}]; 
  dispatch(SetSpeechResult("analysing speech..."));
};

[@react.component]
let make = (~message) => {
  let (_state, dispatch) = React.useReducer(
    (state, action) => 
      switch (action) {
      | SetSpeechResult(txt) => { speechResult: txt }
      }, {speechResult: ""},
    );
  <div onClick={(_e) => handleClick(_e, dispatch)}>
    {ReasonReact.string(message)}
  </div>
};
