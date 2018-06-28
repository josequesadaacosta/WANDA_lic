
#include "mixer.h"


//OBJECT CREATION

// GUItool: begin automatically generated code
AudioInputI2SQuad        i2s_quad1;//xy=174,364
AudioMixer4              gain1; //xy=343,280
AudioMixer4              gain2; //xy=345,444
AudioFilterBiquad        high1; //xy=544,224
AudioFilterBiquad        low1; //xy=544,331
AudioFilterBiquad        medium1; //xy=546,278
AudioFilterBiquad        high2;  //xy=546,388
AudioFilterBiquad        low2; //xy=546,495
AudioFilterBiquad        medium2; //xy=548,442
AudioMixer4              eq1; //xy=708,282
AudioMixer4              eq2; //xy=710,446
AudioAmplifier           l2; //xy=945,471
AudioAmplifier           l1; //xy=947,316
AudioAmplifier           r2; //xy=948,411
AudioAmplifier           r1;           //xy=950,256
AudioMixer4              l; //xy=1141,447
AudioMixer4              r; //xy=1144,293
AudioFilterBiquad        r_high_master; //xy=1313,233
AudioFilterBiquad        r_low_master; //xy=1313,340
AudioFilterBiquad        r_medium_master; //xy=1315,287
AudioFilterBiquad        l_high_master; //xy=1315,397
AudioFilterBiquad        l_low_master; //xy=1315,504
AudioFilterBiquad        l_medium_master; //xy=1317,451
AudioMixer4              r_eq_master; //xy=1477,291
AudioMixer4              l_eq_master; //xy=1479,455
AudioAmplifier           r_master; //xy=1620,291
AudioAmplifier           l_master; //xy=1623,456
AudioOutputI2S           i2sout; //xy=1769,373
AudioConnection          patchCord1(i2s_quad1, 0, gain1, 0);
AudioConnection          patchCord2(i2s_quad1, 1, gain1, 1);
AudioConnection          patchCord3(i2s_quad1, 2, gain2, 0);
AudioConnection          patchCord4(i2s_quad1, 3, gain2, 1);
AudioConnection          patchCord5(gain1, high1);
AudioConnection          patchCord6(gain1, medium1);
AudioConnection          patchCord7(gain1, low1);
AudioConnection          patchCord8(gain2, high2);
AudioConnection          patchCord9(gain2, medium2);
AudioConnection          patchCord10(gain2, low2);
AudioConnection          patchCord11(high1, 0, eq1, 0);
AudioConnection          patchCord12(low1, 0, eq1, 2);
AudioConnection          patchCord13(medium1, 0, eq1, 1);
AudioConnection          patchCord14(high2, 0, eq2, 0);
AudioConnection          patchCord15(low2, 0, eq2, 2);
AudioConnection          patchCord16(medium2, 0, eq2, 1);
AudioConnection          patchCord17(eq1, r1);
AudioConnection          patchCord18(eq1, l1);
AudioConnection          patchCord19(eq2, r2);
AudioConnection          patchCord20(eq2, l2);
AudioConnection          patchCord21(l2, 0, l, 1);
AudioConnection          patchCord22(l1, 0, l, 0);
AudioConnection          patchCord23(r2, 0, r, 1);
AudioConnection          patchCord24(r1, 0, r, 0);
AudioConnection          patchCord25(l, l_high_master);
AudioConnection          patchCord26(l, l_medium_master);
AudioConnection          patchCord27(l, l_low_master);
AudioConnection          patchCord28(r, r_high_master);
AudioConnection          patchCord29(r, r_medium_master);
AudioConnection          patchCord30(r, r_low_master);
AudioConnection          patchCord31(r_high_master, 0, r_eq_master, 0);
AudioConnection          patchCord32(r_low_master, 0, r_eq_master, 2);
AudioConnection          patchCord33(r_medium_master, 0, r_eq_master, 1);
AudioConnection          patchCord34(l_high_master, 0, l_eq_master, 0);
AudioConnection          patchCord35(l_low_master, 0, l_eq_master, 2);
AudioConnection          patchCord36(l_medium_master, 0, l_eq_master, 1);
AudioConnection          patchCord37(r_eq_master, r_master);
AudioConnection          patchCord38(l_eq_master, l_master);
AudioConnection          patchCord39(r_master, 0, i2sout, 0);
AudioConnection          patchCord40(l_master, 0, i2sout, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=338,200
AudioControlSGTL5000     sgtl5000_2;
// GUItool: end automatically generated code



// Method definition
float lineal(float input, int max){
	input = input/max;
	input = (input*50)-10;
	input = 10^(input/20);
	return input
}

void setGain(int analog_return)
{
  if(gain){
  gain_i = gain;
  }
  gain = static_cast<float>analog_return;
 }

float getGain(){
  return gain;  
}

float getGain_i(){
  return gain_i;  
}

void setHp(int analog_return)
{
  if(hp){
  hp_i = hp;
  }
  hp = static_cast<float>analog_return;
 }

float getHp(){
  return hp;  
}

float getHp_i(){
  return hp_i;  
}

void setBpgain(int analog_return)
{
  if(bpgain){
  bpgain_i = bpgain;
  }
  bpgain = static_cast<float>analog_return;
 }

float getBpgain(){
  return bpgain;  
}

float getBpgain_i(){
  return bpgain_i;  
}

void setBpfreq(int analog_return)
{
  if(bpfreq){
  bpfreq_i = bpfreq;
  }
  bpfreq = static_cast<float>analog_return;
 }

float getBpfreq(){
  return bpfreq;  
}

float getBpfreq_i(){
  return bpfreq_i;  
}

void setLp(int analog_return)
{
  if(lp){
  lp_i = lp;
  }
  lp = static_cast<float>analog_return;
 }

float getLp(){
  return lp;  
}

float getLp_i(){
  return lp_i;  
}

void setPan(int analog_return)
{
  if(pan){
  r_i = r;
  }
  r = static_cast<float>analog_return;
 }

float getR(){
  r = pan;
  return r;  
}

float getR_i(){
  r = r_i;
  return r;  
}

float getL(){
  l = 1-pan;
  return l;  
}

void setLevel(int analog_return)
{
  if(level){
  level_i = level;
  }
  level = static_cast<float>analog_return;
 }

float getLevel(){
  return level;  
}

float getLevel_i(){
  return level_i;  
}



void setup() {
  Serial.begin(9600);
  AudioMemory(12);
  sgtl5000_1.enable();
  sgtl5000_1.volume(1);
  sgtl5000_1.inputSelect(AUDIO_INPUT_MIC);
  //sgtl5000_1.inputSelect(AUDIO_INPUT_LINEIN);
  sgtl5000_1.micGain(1);
  
  int max = 1023;
  
  //Create channel objects
  channel ch1;
  channel ch2;
  channel master;
  
  
  //Read variables
  //
  //
  //DO PIN LAYOUT
  //Declar bounces para el switch de activación
  //0 ch1 1 ch2
  //
  //
  
  if(!switch){
  int i = analogRead();
  ch1.setGain(i);
  int i = analogRead();
  ch1.setHp(i);
  int i = analogRead();
  ch1.setBpgain(i);
  int i = analogRead();
  ch1.setBpfreq(i);
  int i = analogRead();
  ch1.setLp(i);
  int i = analogRead();
  ch1.setBpgain(i);
  int i = analogRead();
  ch1.setBpfreq(i);
  int i = analogRead();
  ch1.setLp(i);
  int i = analogRead();
  ch1.setPan(i);
  int i = analogRead();
  ch1.setLevel(i); 
  
  }else{
	  
  int i = analogRead();
  ch2.setGain(i);
  int i = analogRead();
  ch2.setHp(i);
  int i = analogRead();
  ch2.setBpgain(i);
  int i = analogRead();
  ch2.setBpfreq(i);
  int i = analogRead();
  ch2.setLp(i);
  int i = analogRead();
  ch2.setBpgain(i);
  int i = analogRead();
  ch2.setBpfreq(i);
  int i = analogRead();
  ch2.setLp(i);
  int i = analogRead();
  ch2.setPan(i);
  int i = analogRead();
  ch2.setLevel(i);
  
  }

  
  //Set non-changing parameters
  //Channel 1
  high1.setHighpass(0,12000,0.7071);
  low1.setLowpass(0,80,0.7071);
  
  //Channel 2
  high2.setHighpass(0,12000,0.7071);
  low2.setLowpass(0,80,0.7071);
  
  //Master
  r_high_master.setHighpass(0,12000,0.7071);
  r_low_master.setLowpass(0,80,0.7071);
  l_high_master.setHighpass(0,12000,0.7071);
  l_low_master.setLowpass(0,80,0.7071);
  
  
}

void loop() {
	
	//Modify gain
	if(ch1.getGain() != ch1.getGain_i()){
		gain1.gain(0,lineal(ch1.getGain(),max));
		gain1.gain(1,lineal(ch1.getGain(),max));
	}
	
	if(ch2.getGain() != ch2.getGain_i()){
		gain2.gain(0,lineal(ch2.getGain(),max));
		gain2.gain(1,lineal(ch2.getGain(),max));
	}
	
	
	//Modify 3 band eq
	if(ch1.getHp() != ch1.getHp_i()){
		eq1.gain(0,lineal(ch1.getHp(),max));
	}
	if(ch1.getBpgain() != ch1.getBpgain_i()){
		eq1.gain(1,lineal(ch1.getBpgain(),max));
	}
	if(ch1.getBpfreq() != ch1.getBpfreq_i()){
		medium1.setBandpass(0, ch1.getBpfreq(), 0.707);
	}
	if(ch1.getLp() != ch1.getLp_i()){
		eq1.gain(2,lineal(ch1.getLp(),max));
	}
	
	if(ch2.getHp() != ch2.getHp_i()){
		eq2.gain(0,lineal(ch2.getHp(),max));
	}
	if(ch2.getBpgain() != ch2.getBpgain_i()){
		eq2.gain(1,lineal(ch2.getBpgain(),max));
	}
	if(ch2.getBpfreq() != ch2.getBpfreq_i()){
		medium2.setBandpass(0, ch2.getBpfreq(), 0.707);
	}
	if(ch2.getLp() != ch2.getLp_i()){
		eq2.gain(2,lineal(ch2.getLp(),max));
	}
	
	//Modify pan
	if(ch1.getR() != ch1.getR_i()){
		r1.gain(ch1.getR());
		l1.gain(ch1.getL());
	}
	
	if(ch2.getR() != ch2.getR_i()){
		r2.gain(ch2.getR());
		l2.gain(ch2.getL());
	}
	
	//Modify level
	if(ch1.getLevel() != ch1.getLevel_i()){
		r.gain(0,lineal(ch1.getLevel(),max));
		l.gain(0,lineal(ch1.getLevel(),max));
	}
	
	if(ch2.getLevel() != ch2.getLevel_i()){
		r.gain(0,lineal(ch2.getLevel(),max));
		l.gain(0,lineal(ch2.getLevel(),max));
	}
	
	
	//Master 
	//Eq
	if(master.getHp() != master.getHp_i()){
		r_eq_master.gain(0,lineal(master.getHp(),max));
		l_eq_master.gain(0,lineal(master.getHp(),max));
	}
	
	if(master.getBpgain() != master.getBpgain_i()){
		r_eq_master.gain(1,lineal(master.getBpgain(),max));
		l_eq_master.gain(1,lineal(master.getBpgain(),max));
	}
	
	if(master.getBpfreq() != master.getBpfreq_i()){
		r_medium_master.setBandpass(0, master.getBpfreq(), 0.707);
		l_medium_master.setBandpass(0, master.getBpfreq(), 0.707);
	}
	
	if(master.getLp() != master.getLp_i()){
		r_eq_master.gain(2,lineal(master.getLp(),max));
		l_eq_master.gain(2,lineal(master.getLp(),max));
	}

	
	//Level	
	
	if(master.getLevel() != master.getLevel_i()){
		r_master.gain(0,lineal(master.getLevel(),max));
		l_master.gain(0,lineal(master.getLevel(),max));
	}

	delay(100);

	//Reread
if(!switch){
  int i = analogRead();
  ch1.setGain(i);
  int i = analogRead();
  ch1.setHp(i);
  int i = analogRead();
  ch1.setBpgain(i);
  int i = analogRead();
  ch1.setBpfreq(i);
  int i = analogRead();
  ch1.setLp(i);
  int i = analogRead();
  ch1.setBpgain(i);
  int i = analogRead();
  ch1.setBpfreq(i);
  int i = analogRead();
  ch1.setLp(i);
  int i = analogRead();
  ch1.setPan(i);
  int i = analogRead();
  ch1.setLevel(i); 
  
  }else{
	  
  int i = analogRead();
  ch2.setGain(i);
  int i = analogRead();
  ch2.setHp(i);
  int i = analogRead();
  ch2.setBpgain(i);
  int i = analogRead();
  ch2.setBpfreq(i);
  int i = analogRead();
  ch2.setLp(i);
  int i = analogRead();
  ch2.setBpgain(i);
  int i = analogRead();
  ch2.setBpfreq(i);
  int i = analogRead();
  ch2.setLp(i);
  int i = analogRead();
  ch2.setPan(i);
  int i = analogRead();
  ch2.setLevel(i);
  
  }
	

		

}

