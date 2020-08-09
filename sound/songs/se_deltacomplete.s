	.include "MPlayDef.s"

	.equ	deltase_complete_grp, voicegroup127
	.equ	deltase_complete_pri, 5
	.equ	deltase_complete_rev, reverb_set+50
	.equ	deltase_complete_mvl, 125
	.equ	deltase_complete_key, 0
	.equ	deltase_complete_tbs, 1
	.equ	deltase_complete_exg, 1
	.equ	deltase_complete_cmp, 1

	.section .rodata
	.global	deltase_complete
	.align	2

@**************** Track 1 (Midi-Chn.1) ****************@

deltase_complete_1:
	.byte	KEYSH , deltase_complete_key+0
@ 000   ----------------------------------------
	.byte	TEMPO , 128*deltase_complete_tbs/2
	.byte		VOICE , 102
	.byte		VOL   , 127*deltase_complete_mvl/mxv
	.byte		N22   , Cn3 , v127
	.byte	W04
	.byte	W05
@ 001   ----------------------------------------
	.byte	W12
@ 002   ----------------------------------------
	.byte	FINE

@******************************************************@
	.align	2

deltase_complete:
	.byte	1	@ NumTrks
	.byte	0	@ NumBlks
	.byte	deltase_complete_pri	@ Priority
	.byte	deltase_complete_rev	@ Reverb.

	.word	deltase_complete_grp

	.word	deltase_complete_1

	.end
