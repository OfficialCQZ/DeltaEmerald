	.include "MPlayDef.s"

	.equ	deltase_select_grp, voicegroup127
	.equ	deltase_select_pri, 5
	.equ	deltase_select_rev, reverb_set+50
	.equ	deltase_select_mvl, 125
	.equ	deltase_select_key, 0
	.equ	deltase_select_tbs, 1
	.equ	deltase_select_exg, 1
	.equ	deltase_select_cmp, 1

	.section .rodata
	.global	deltase_select
	.align	2

@**************** Track 1 (Midi-Chn.1) ****************@

deltase_select_1:
	.byte	KEYSH , deltase_select_key+0
@ 000   ----------------------------------------
	.byte	TEMPO , 128*deltase_select_tbs/2
	.byte		VOICE , 100
	.byte		VOL   , 127*deltase_select_mvl/mxv
	.byte		N01   , Cn3 , v127
	.byte	W02
	.byte	W03
	.byte	W05
	.byte	W16
	.byte	W05
@ 001   ----------------------------------------
	.byte	W12
@ 002   ----------------------------------------
	.byte	FINE

@******************************************************@
	.align	2

deltase_select:
	.byte	1	@ NumTrks
	.byte	0	@ NumBlks
	.byte	deltase_select_pri	@ Priority
	.byte	deltase_select_rev	@ Reverb.

	.word	deltase_select_grp

	.word	deltase_select_1

	.end
