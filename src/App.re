external toVoice : 'a => SpeechSynthesis.voice = "%identity";

let synth = SpeechSynthesis.speechSynthesis;

type action =
  | SetUtter(SpeechSynthesis.speech)
  | SetUtterance(string)
  | SetSpeechResult(string);

type state = {
  speechResult: string,
  utterance: string,
  utter: SpeechSynthesis.speech
};

let recognition = WebSpeechAPI.recognition;
let grammar = "#JSGF V1.0; grammar colors; public <words> =";

WebSpeechAPI.speechRecognitionList##addFromString(grammar, 1);

let str = ReasonReact.string;
let css = ReactDOMRe.Style.make;
let valueFromEvent = evt : string => (
  evt
  |> ReactEvent.Form.target
  )##value;

let handleClick = (_event, dispatch) => {
  Js.log("listening...");
  recognition##start();
  dispatch(SetSpeechResult("analysing speech..."));
  recognition##onresult #= [%raw {|
    (event) => 
      //dangerously adding raw javascript output, if any changes occur in reducer, you may need to update the line below
      Curry._1(dispatch, /* SetSpeechResult */Block.__(2, [event.results[event.results.length - 1][0].transcript]))
  |}]; 
};

[@react.component]
let make = () => {
  let (state, dispatch) = React.useReducer(
    (state, action) => 
      switch (action) {
      | SetSpeechResult(txt) => {...state, speechResult: txt}
      | SetUtter(utterance) => {...state, utter: utterance}
      | SetUtterance(txt) => {...state, utterance: txt}
      }, {
        speechResult: "", 
        utterance: "I am denice", 
        utter: SpeechSynthesis.speechSynthesisUtterance("") 
      },
    );
  let _ = React.useEffect1(() => {
    SetUtter(
      state.utterance
      |> SpeechSynthesis.speechSynthesisUtterance
    ) |> dispatch
    None;
  }, [|state.utterance|]);

  <div>
    <div style=css(~padding="10px", ~backgroundColor="cornsilk",())>
      <button onClick={(_e) => handleClick(_e, dispatch)}>
        {str("Record")}
      </button>
      (
        if(state.speechResult |> String.length > 0) {
          <div>
            <p>{str(state.speechResult)}</p>
            <button 
               onClick=(_event => synth##speak(
                 state.speechResult
                 |> SpeechSynthesis.speechSynthesisUtterance
               ))
            >
               {"Speak Result!" |> str}
            </button>
          </div>
        } else {
          <div></div>
        }
      ) 
    </div>
    <div style=css(~padding="10px", ~backgroundColor="chartreuse", ())>
      
    </div>
    <div style=css(~padding="10px", ~backgroundColor="chartreuse", ())>
      <input type_="text" onChange=(evt => dispatch(SetUtterance(evt |> valueFromEvent)))/>
      <button 
         onClick=(_event => synth##speak(state.utter))
      >
         {"Speak!" |> str}
      </button>
    </div>
  </div>
};

module Css = {
  let container1 = css(
    ~padding="10px"
  )
}
