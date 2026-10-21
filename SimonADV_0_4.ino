#if defined(SIMULATOR)
  // --- PC SIMULATOR MODE ---
  #define LGFX_USE_V1
  #include <LovyanGFX.hpp>
  #include <LGFX_AUTODETECT.hpp>
  
  static LGFX display;
  
  void initHardware() {
      display.init();
      display.setRotation(1);
      display.setInitWidth(240);
      display.setInitHeight(135);
  }

  void updateInput() {
      // Input is handled natively by SDL events in PC mode
  }

#else
  // --- REAL CARDPUTER HARDWARE MODE ---
  #include <M5Cardputer.h>
  #define display M5Cardputer.Display

  void initHardware() {
      auto cfg = M5.config();
      M5Cardputer.begin(cfg, true);
      M5Cardputer.Display.setRotation(1);
  }

  void updateInput() {
      M5Cardputer.update();
  }
#endif

// =========================================================================
// YOUR CODE STARTS HERE - THIS PORTION IS 100% SHARED BETWEEN BOTH TARGETS
// =========================================================================

int counter = 0;

void drawScreen() {
    display.startWrite();
    display.fillScreen(TFT_BLACK);
    
    // Draw Header Box
    display.fillRect(0, 0, 240, 25, TFT_BLUE);
    display.setTextColor(TFT_WHITE);
    display.setTextSize(1.5);
    display.setTextDatum(MC_DATUM);
    display.drawString("Cardputer App Preview", 120, 12);

    // Draw Content
    display.setTextSize(1);
    display.drawString("Testing UI Layout On PC", 120, 50);
    
    // Draw Dynamic Counter Bar
    display.drawRect(20, 80, 200, 20, TFT_WHITE);
    int barWidth = map(counter % 100, 0, 100, 0, 196);
    display.fillRect(22, 82, barWidth, 16, TFT_GREEN);

    display.drawString("Press ENTER / Space in terminal", 120, 118);
    display.endWrite();
}

void setup() {
    initHardware();
    drawScreen();
}

void loop() {
    updateInput();
    
    // Increment counter for demonstration
    counter++;
    drawScreen();
    delay(50);
}