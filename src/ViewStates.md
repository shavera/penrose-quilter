# View States

## State Machine

```mermaid

stateDiagram-v2
  [*] --> DragPan : AltKey_Pressed
  [*] --> Select : ShiftKey_Pressed

  DragPan --> [*] : AltKey_Released
  Select --> [*] : ShiftKey_Released

```
