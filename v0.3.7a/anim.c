#ifndef __ANIM__C__
#define __ANIM__C__

#include "data.c"

int __rnd_delay(oz_Animation* anim)
{
	return (rand() % anim->random.max_delay) + anim->random.min_delay;
}

int __rnd_frame(oz_Animation* anim)
{
	return (rand() % anim->frame_count);
}

oz_CharData oz_getAnimationFrame(oz_Animation* anim)
{
	if (anim->_static)
		return anim->frames[0];

	anim->_count  += (14 * *delta);
	if (anim->_count < anim->delay)
		return anim->frames[anim->current_frame];
	anim->_count = 0;
	if (anim->random.rnd_delay)
		anim->delay = __rnd_delay(anim);

	if (anim->random.rnd_frames)
	{
		anim->current_frame = __rnd_frame(anim);
		return anim->frames[anim->current_frame];
	}
	else if (++(anim->current_frame) < anim->frame_count)
		return anim->frames[anim->current_frame];

	anim->current_frame = 0;
	return anim->frames[0];
}

void oz_fillRndInfo(oz_Animation* anim, int min_delay, int max_delay, bool rnd_delay, bool rnd_frames)
{
	anim->random.min_delay = min_delay;
	anim->random.max_delay = max_delay;
	anim->random.rnd_delay = rnd_delay;
	anim->random.rnd_frames = rnd_frames;
}

oz_Animation oz_buildStaticAnimation(oz_CharData cd)
{
	oz_Animation anim;
	anim.frames[0].ascii = cd.ascii;
	anim.frames[0].color = cd.color;
	anim._static = true;
	anim.frame_count = 1;
	oz_fillRndInfo(&anim, 5, 10, false, false);
	return anim;
}

oz_Animation oz_buildAnimation(int frame_count, int delay)
{
	oz_Animation anim;
	if (frame_count > MAX_ANIM_LEN)
		frame_count = MAX_ANIM_LEN;
	if (delay < 1)
		delay = 1;
	anim.delay = delay;
	anim.frame_count = frame_count;
	anim.current_frame = 0;
	anim._count = 0;
	anim._static = false;
	oz_fillRndInfo(&anim, 5, 10, false, false);
	for (int i = 0; i < frame_count; i++)
	{
		anim.frames[i].ascii = ' ';
		anim.frames[i].color.bg_color = 0;
		anim.frames[i].color.fg_color = 0;
		anim.frames[i].color.transparent_bg = false;
	}
	return anim;
}

oz_Animation oz_buildRndAnimation(int frame_count, int min_delay, int max_delay, bool rnd_delay, bool rnd_frames)
{
	oz_Animation anim = oz_buildAnimation(frame_count, 0);
	oz_fillRndInfo(&anim, min_delay, max_delay, rnd_delay, rnd_frames);
	if (!rnd_delay)
		anim.delay = min_delay;
	return anim;
}

void oz_fillAnimation(oz_Animation* anim, oz_CharData cd[MAX_ANIM_LEN])
{
	for (int i = 0; i < anim->frame_count; i++)
	{
		anim->frames[i].ascii = cd[i].ascii;
		anim->frames[i].color = cd[i].color;
	}
}

#endif
