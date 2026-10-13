Step-by-Step Wiring Instructions

Set up the Main Power Distribution
  Configure your DC-DC Buck Converter (e.g., an LM2596 module) to output exactly $5.0\text{V}$.
  Connect the Negative ($-$) wire from your 2S LiPo battery ($7.4\text{V}$ nominal) to the IN$-$ of the buck converter.
  Connect the Positive ($+$) wire from the 2S LiPo to the IN$+$ of the buck converter.
  The OUT$+$ ($5\text{V}$) of the converter is now your Servo Power Rail.
  The OUT$-$ of the converter is now your System Ground Rail.
