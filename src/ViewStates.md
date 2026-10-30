# View States

## State Machine

```mermaid

stateDiagram-v2
  [*] --> ready 

  ready --> dragPan : AltKey_Pressed
  dragPan --> ready : AltKey_Released

  ready --> bandSelect : ShiftKey_Pressed
  bandSelect --> ready : ShiftKey_Released
```
