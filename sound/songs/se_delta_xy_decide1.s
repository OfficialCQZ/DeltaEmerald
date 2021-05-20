	.include "MPlayDef.s"

	.equ	deltase_xy_decide1_grp, voicegroup259
	.equ	deltase_xy_decide1_pri, 5
	.equ	deltase_xy_decide1_rev, reverb_set+50
	.equ	deltase_xy_decide1_mvl, 125
	.equ	deltase_xy_decide1_key, 0
	.equ	deltase_xy_decide1_tbs, 1
	.equ	deltase_xy_decide1_exg, 1
	.equ	deltase_xy_decide1_cmp, 1

	.section .rodata
	.global	deltase_xy_decide1
	.align	2

@**************** Track 1 (Midi-Chn.1) ****************@

deltase_xy_decide1_1:
	.byte	KEYSH , deltase_xy_decide1_key+0
@ 000   ----------------------------------------
	.byte	TEMPO , 128*deltase_xy_decide1_tbs/2
	.byte		VOICE , 104
	.byte		VOL   , 127*deltase_xy_decide1_mvl/mxv
	.byte		N22   , Cn3 , v127
	.byte	W04
	.byte	W05
@ 001   ----------------------------------------
	.byte	W12
@ 002   ----------------------------------------
	.byte	FINE

@******************************************************@
	.align	2

deltase_xy_decide1:
	.byte	1	@ NumTrks
	.byte	0	@ NumBlks
	.byte	deltase_xy_decide1_pri	@ Priority
	.byte	deltase_xy_decide1_rev	@ Reverb.

	.word	deltase_xy_decide1_grp

	.word	deltase_xy_decide1_1

	.end
