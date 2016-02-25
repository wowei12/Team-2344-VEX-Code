#ifndef INCLUDE_MUSIC_H
#define INCLUDE_MUSIC_H

/****************************************************************/

/****************************************************************/

/****************************************************************/

void playPacMan()
{
	playTone(493.88, 12.5); // B4 1
	wait1Msec(125);
	playTone(987.77, 12.5); // B5 e
	wait1Msec(125);
	playTone(739.99, 12.5); // F#5 +
	wait1Msec(125);
	playTone(622.25, 12.5); // Eb5 a
	wait1Msec(125);
	playTone(987.77, 6.25); // B5 2
	wait1Msec(62.5);
	playTone(739.99, 12.5); // F#5 +a
	wait1Msec(125);
	playTone(622.25, 25); // Eb5 a
	wait1Msec(250);
	//***********//
	playTone(523.25, 12.5); // C5 3
	wait1Msec(125);
	playTone(1046.50, 12.5); // C6 e
	wait1Msec(125);
	playTone(783.99, 12.5); // G5 +
	wait1Msec(125);
	playTone(659.25, 12.5); // E5 a
	wait1Msec(125);
	playTone(1046.50, 6.25); // C6 4
	wait1Msec(62.5);
	playTone(783.99, 12.5); // G5 +a
	wait1Msec(125);
	playTone(659.25, 25); // E5 a
	wait1Msec(250);
	//********//
	playTone(493.88, 12.5); // B4 1
	wait1Msec(125);
	playTone(987.77, 12.5); // B5 e
	wait1Msec(125);
	playTone(739.99, 12.5); // F#5 +
	wait1Msec(125);
	playTone(622.25, 12.5); // Eb5 a
	wait1Msec(125);
	playTone(987.77, 6.25); // B5 2
	wait1Msec(62.5);
	playTone(739.99, 12.5); // F#5 +a
	wait1Msec(125);
	playTone(622.25, 25); // Eb5 a
	wait1Msec(250);
	//*********//
	playTone(622.25, 6.25); // Eb5 3
	wait1Msec(62.5);
	playTone(659.25, 6.25); // E5 +a
	wait1Msec(62.5);
	playTone(698.46, 12.5); // F5 a
	wait1Msec(125);

	playTone(698.46, 6.25); // F5 3
	wait1Msec(62.5);
	playTone(739.99, 6.25); // F#5 +a
	wait1Msec(62.5);
	playTone(783.99, 12.5); // G5 +a
	wait1Msec(125);

	playTone(783.99, 6.25); // G5 3
	wait1Msec(62.5);
	playTone(830.61, 6.25); // Ab5 +a
	wait1Msec(62.5);
	playTone(880.00, 12.5); // A5 +a
	wait1Msec(125);
	playTone(987.77, 25); // G5 +a
	wait1Msec(250);
}

void playPIDSound()
{
	playTone(987.77, 6.25);
}

/****************************************************************/

task triggerPacMan()
{
	playPacMan();
}

/****************************************************************/

#endif
