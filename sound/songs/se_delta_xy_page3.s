	.include "MPlayDef.s"

	.equ	deltase_xy_page3_grp, voicegroup127
	.equ	deltase_xy_page3_pri, 5
	.equ	deltase_xy_page3_rev, reverb_set+50
	.equ	deltase_xy_page3_mvl, 125
	.equ	deltase_xy_page3_key, 0
	.equ	deltase_xy_page3_tbs, 1
	.equ	deltase_xy_page3_exg, 1
	.equ	deltase_xy_page3_cmp, 1

	.section .rodata
	.global	deltase_xy_page3
	.align	2

@**************** Track 1 (Midi-Chn.1) ****************@

deltase_xy_page3_1:
	.byte	KEYSH , deltase_xy_page3_key+0
@ 000   ----------------------------------------
	.byte	TEMPO , 128*deltase_xy_page3_tbs/2
	.byte		VOICE , 105
	.byte		VOL   , 127*deltase_xy_page3_mvl/mxv
	.byte		N22   , Cn3 , v127
	.byte	W04
	.byte	W05
@ 001   ----------------------------------------
	.byte	W12
@ 002   ----------------------------------------
	.byte	FINE

@******************************************************@
	.align	2

deltase_xy_page3:
	.byte	1	@ NumTrks
	.byte	0	@ NumBlks
	.byte	deltase_xy_page3_pri	@ Priority
	.byte	deltase_xy_page3_rev	@ Reverb.

	.word	deltase_xy_page3_grp

	.word	deltase_xy_page3_1

	.end
