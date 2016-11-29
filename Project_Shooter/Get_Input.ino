int buttonsState[ButtonNum];
const uint32_t physicalButtons[ButtonNum] = {PE_0 , PD_2, PF_4, PF_0}; //corresponds with buttons up, down, left, right
const uint32_t physicalSwitches[SwitchNum] = {PA_6, PA_7};        //corresponds with switch left, right

void InputInit() {
  for (int i = 0; i < ButtonNum; i++) {
    buttonsState[i] = 0;
    if (physicalButtons[i] == PF_4)
      pinMode(physicalButtons[i], INPUT_PULLUP);
    else
      pinMode(physicalButtons[i], INPUT);
  }

  for (int i = 0; i < SwitchNum; i++) {
    pinMode(physicalSwitches[i], INPUT);
  }
}

void InputTick() {
  for (int i = 0; i < ButtonNum; i++) {
    bool previousState = buttonsState[i];
    buttonsState[i] = digitalRead(physicalButtons[i]);
    gameController.setButton(i, !previousState && buttonsState[i]);
  }

  for (int i = 0; i < SwitchNum; i++) {
    gameController.setSwitch(i, digitalRead(physicalSwitches[i]));
  }
}

