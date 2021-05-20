	.include "MPlayDef.s"

	.equ	deltase_selected_grp, voicegroup259
	.equ	deltase_selected_pri, 5
	.equ	deltase_selected_rev, reverb_set+50
	.equ	deltase_selected_mvl, 125
	.equ	deltase_selected_key, 0
	.equ	deltase_selected_tbs, 1
	.equ	deltase_selected_exg, 1
	.equ	deltase_selected_cmp, 1

	.section .rodata
	.global	deltase_selected
	.align	2

@**************** Track 1 (Midi-Chn.1) ****************@

deltase_selected_1:
	.byte	KEYSH , deltase_selected_key+0
@ 000   ----------------------------------------
	.byte	TEMPO , 128*deltase_selected_tbs/2
	.byte		VOICE , 101
	.byte		VOL   , 127*deltase_selected_mvl/mxv
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

deltase_selected:
	.byte	1	@ NumTrks
	.byte	0	@ NumBlks
	.byte	deltase_selected_pri	@ Priority
	.byte	deltase_selected_rev	@ Reverb.

	.word	deltase_selected_grp

	.word	deltase_selected_1

	.end
