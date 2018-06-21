
#include "mixer.h"


//OBJECT CREATION
// Inputs
AudioInputI2S            input1;           //xy=189,178
AudioInputI2S            input2;           //xy=191,342
AudioInputI2S            input3; //xy=192,516


//Channel gain, stereo -> mono
AudioMixer4              gain1; //xy=331,191
AudioMixer4              gain2; //xy=333,355
AudioMixer4              gain3; //xy=334,529


//3 band channel eq
//Channel1
AudioFilterBiquad        high1; //xy=532,135
AudioFilterBiquad        medium1; //xy=534,189
AudioFilterBiquad        low1; //xy=532,242
AudioMixer4              eq1; //xy=696,193

//Channel2
AudioFilterBiquad        high3; //xy=531,472
AudioFilterBiquad        medium3; //xy=533,526
AudioFilterBiquad        low3; //xy=531,579
AudioMixer4              eq2; //xy=698,357

//Channel3
AudioFilterBiquad        high2;  //xy=534,299
AudioFilterBiquad        medium2; //xy=536,353
AudioFilterBiquad        low2; //xy=534,406
AudioMixer4              eq3; //xy=699,531


//Channel pan
//Channel1
AudioAmplifier           r1; //xy=938,167
AudioAmplifier           l1; //xy=935,227

//Channel2
AudioAmplifier           r2; //xy=936,322
AudioAmplifier           l2; //xy=933,382

//Channel3
AudioAmplifier           r3; //xy=935,483
AudioAmplifier           l3; //xy=932,543


//Master (for 4+ channels, use mixers in stages)
AudioMixer4              l; //xy=1141,447
AudioMixer4              r; //xy=1144,293


//3 band master eq
//r
AudioFilterBiquad        r_high_master; //xy=1313,233
AudioFilterBiquad        r_medium_master; //xy=1315,287
AudioFilterBiquad        r_low_master; //xy=1313,340
AudioMixer4              r_eq_master; //xy=1477,291

//l
AudioFilterBiquad        l_high_master; //xy=1315,397
AudioFilterBiquad        l_medium_master; //xy=1317,451
AudioFilterBiquad        l_low_master; //xy=1315,504
AudioMixer4              l_eq_master; //xy=1479,455


//Master pan
AudioAmplifier           r_master; //xy=1620,291
AudioAmplifier           l_master; //xy=1623,456


//Output
AudioOutputI2S           i2sout; //xy=1769,373



//CONNECTIONS
AudioConnection          patchCord1(input1, 0, gain1, 0);
AudioConnection          patchCord2(input1, 1, gain1, 1);
AudioConnection          patchCord3(input2, 0, gain2, 0);
AudioConnection          patchCord4(input2, 1, gain2, 1);
AudioConnection          patchCord5(input3, 0, gain3, 0);
AudioConnection          patchCord6(input3, 1, gain3, 1);
AudioConnection          patchCord7(gain1, high1);
AudioConnection          patchCord8(gain1, medium1);
AudioConnection          patchCord9(gain1, low1);
AudioConnection          patchCord10(gain2, high2);
AudioConnection          patchCord11(gain2, medium2);
AudioConnection          patchCord12(gain2, low2);
AudioConnection          patchCord13(gain3, high3);
AudioConnection          patchCord14(gain3, medium3);
AudioConnection          patchCord15(gain3, low3);
AudioConnection          patchCord16(high1, 0, eq1, 0);
AudioConnection          patchCord17(high3, 0, eq3, 0);
AudioConnection          patchCord18(low1, 0, eq1, 2);
AudioConnection          patchCord19(low3, 0, eq3, 2);
AudioConnection          patchCord20(medium1, 0, eq1, 1);
AudioConnection          patchCord21(medium3, 0, eq3, 1);
AudioConnection          patchCord22(high2, 0, eq2, 0);
AudioConnection          patchCord23(low2, 0, eq2, 2);
AudioConnection          patchCord24(medium2, 0, eq2, 1);
AudioConnection          patchCord25(eq1, r1);
AudioConnection          patchCord26(eq1, l1);
AudioConnection          patchCord27(eq2, r2);
AudioConnection          patchCord28(eq2, l2);
AudioConnection          patchCord29(eq3, r3);
AudioConnection          patchCord30(eq3, l3);
AudioConnection          patchCord31(l3, 0, l, 2);
AudioConnection          patchCord32(l2, 0, l, 1);
AudioConnection          patchCord33(l1, 0, l, 0);
AudioConnection          patchCord34(r3, 0, r, 2);
AudioConnection          patchCord35(r2, 0, r, 1);
AudioConnection          patchCord36(r1, 0, r, 0);
AudioConnection          patchCord37(l, l_high_master);
AudioConnection          patchCord38(l, l_medium_master);
AudioConnection          patchCord39(l, l_low_master);
AudioConnection          patchCord40(r, r_high_master);
AudioConnection          patchCord41(r, r_medium_master);
AudioConnection          patchCord42(r, r_low_master);
AudioConnection          patchCord43(r_high_master, 0, r_eq_master, 0);
AudioConnection          patchCord44(r_low_master, 0, r_eq_master, 2);
AudioConnection          patchCord45(r_medium_master, 0, r_eq_master, 1);
AudioConnection          patchCord46(l_high_master, 0, l_eq_master, 0);
AudioConnection          patchCord47(l_low_master, 0, l_eq_master, 2);
AudioConnection          patchCord48(l_medium_master, 0, l_eq_master, 1);
AudioConnection          patchCord49(r_eq_master, r_master);
AudioConnection          patchCord50(l_eq_master, l_master);
AudioConnection          patchCord51(r_master, 0, i2sout, 0);
AudioConnection          patchCord52(l_master, 0, i2sout, 1);


AudioControlSGTL5000     sgtl5000_1;     //xy=326,111
// GUItool: end automatically generated code




void setup() {
  Serial.begin(9600);
  AudioMemory(12);
  sgtl5000_1.enable();
  sgtl5000_1.volume(1);
  sgtl5000_1.inputSelect(AUDIO_INPUT_MIC);
  //sgtl5000_1.inputSelect(AUDIO_INPUT_LINEIN);
  sgtl5000_1.micGain(1);
  
  
  //Create channel objects
  channel ch1
  channel ch2
  channel ch3
  master master
  
  
  //Read and initialize variables
    //Read gain
	float ch1_gain = ch1.gain();
	float ch2_gain = ch2.gain();
	float ch3_gain = ch3.gain();
	
	//Read 3 band eq parameters
	//Channel 1
	float ch1_hp = ch1.hp();
	float ch1_bpgain = ch1.bpgain();
	uint16_t ch1_bpfreq = ch1.bpfreq();
	float ch1_lp = ch1.lp();
	
	//Channel 2
	ch2.hp = ;
	float ch2_hp = ch2.hp();
	float ch2_bpgain = ch2.bpgain();
	uint16_t ch2_bpfreq = ch2.bpfreq();
	float ch2_lp = ch2.lp();

	//Channel 3
	float ch3_hp = ch3.hp();
	float ch3_bpgain = ch3.bpgain();
	uint16_t ch3_bpfreq = ch3.bpfreq();
	float ch3_lp = ch3.lp();
	
	//Master
	float master_hp = master.hp();
	float master_bpgain = master.bpgain();
	uint16_t master_bpfreq = master.bpfreq();
	float master_lp = master.lp();
	
	
	//Read volume
	float ch1_r = ch1.l();
	float ch2_r = ch2.l();
	float ch3_r = ch3.l();
	float ch1_l = ch1.l();
	float ch2_l = ch2.l();
	float ch3_l = ch3.l();
	float master_r = master.r();
	float master_l = master.l();
	float master_mono = master.mono();
	
  
  
  //Set non-changing parameters
  //Channel 1
  high1.setHighpass(0,12000,0.7071);
  low1.setLowpass(0,80,0.7071);
  
  //Channel 2
  high2.setHighpass(0,12000,0.7071);
  low2.setLowpass(0,80,0.7071);
  
  //Channel 3
  high3.setHighpass(0,12000,0.7071);
  low3.setLowpass(0,80,0.7071);
  
  //Master
  r_high_master.setHighpass(0,12000,0.7071);
  r_low_master.setLowpass(0,80,0.7071);
  l_high_master.setHighpass(0,12000,0.7071);
  l_low_master.setLowpass(0,80,0.7071);
  
  
}

void loop() {
	
	//Modify gain
	if(ch1_gain != ch1.gain()){
		gain1.gain(0,ch1.gain());
		gain1.gain(1,ch1.gain());
	}
	
	
	//Modify 3 band eq
	if(ch1_hp != ch1.hp()){
		eq1.gain(0,ch1.hp());
	}
	if(ch1_bpgain != ch1.bpgain()){
		eq1.gain(1,ch1.bpgain());
	}
	if(ch1_bpfreq != ch1.bpfreq()){
		medium1.setBandpass(0, ch1.bpfreq(), 0.7071);
	}
	if(ch1_lp != ch1.lp()){
		eq1.gain(2,ch1.lp());
	}
	
	//Modify pan
	if(ch1_r != ch1.r()){
		r1.gain(ch1.r());
		l1.gain(ch1.l());
	}
	
	//Modify level
	if(ch1_level != ch1.level()){
		r.gain(0,ch1.level());
		l.gain(0,ch1.level());
	}
	
	
	//Master 
	//Eq
	if(master_hp != master.hp()){
		r_eq_master.gain(0,master.hp());
		l_eq_master.gain(0,master.hp());
	}
	if(master_bpgain != master.bpgain()){
		r_eq_master.gain(1,master.bpgain());
		l_eq_master.gain(1,master.bpgain());
	}
	if(master_bpfreq != master.bpfreq()){
		r_medium_master.setBandpass(0, master.bpfreq(), 0.7071);
		l_medium_master.setBandpass(0, master.bpfreq(), 0.7071);
	}
	if(master_lp != master.lp()){
		r_eq_master.gain(2,master.lp());
		l_eq_master.gain(2,master.lp());
	}
	
	//Level	
	if(master_level != master.level()){
		r_master.gain(0,master.level());
		l_master.gain(0,master.level());
	}
	

		

}

