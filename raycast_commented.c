// Renders a circle around the player (assumed to be in the center of the
// screen), occluding behind solid tiles.
// The core idea is to draw points on the periphery of the circle, then
// draw rays to them, and render along those rays. If a ray intersects a
// solid block, we stop rendering it.

int viewrad=30; // how far the player can see
for(int r=0;r<viewrad*2.5*M_PI+1;r++){
	// a circle of radius r has a circumference of 2*pi*r
	// however, we use 2.5*pi*r to "fill out the circle" (try it out and see)

	float rf=(float)r/viewrad/2.5*2;
	// r is in units, convert to radians

	float dx=0,dy=0;
	// the slope of the current ray

	switch((int)(rf*8/2/M_PI)){
		// we divide the circle in 4 quadrants, and calculate the slopes
		// differently for each one (well, 8 quadrants, since if we divided in
		// 4, we would get a horisontal/vertical split, but we want diagonal)
		// tan=sin/cos, and we rotate clockwise
		/* please refer to this ugly diagram for reference:

   o->y
   |
   v    dx=-1
   x   dy=tan(a)
       \     /
        \   /
   dy=-1 \ / dy=1
   dx=1/  @  dx=1/tan(a)
  tan(a) / \
        /   \
       /dx= 1\
      dy=tan(a)
		*/

		case 7:case 0:dx=-1,dy=sin(rf)/cos(rf);break; // upper quaadrant
		case 1:case 2:dx=cos(rf)/sin(rf),dy=+1;break; // right quadrant
		case 3:case 4:dx=+1,dy=sin(rf)/cos(rf);break; // lower quadrant
		case 5:case 6:dx=cos(rf)/sin(rf),dy=-1;break; // left quadrant
	}

	for(int i=0;i<viewrad;i++){
		// i tells us how far along the ray we are. since the above
		// trigonometrics do not result in a unit slope, we use pythagoras
		// (along with the condition in the for loop) to limit the radius
		// of the circle.
		if(i*i*(dx*dx+dy*dy)>viewrad*viewrad)break;

		int x=i*dx+sx/2+.5;
		int y=i*dy+sy/2+.5;
		// from the slopes, we calculate the exact screen pixel we are at.
		// i*delta tells us how far from the origin we are, screen/2
		// offsets the circle to the center. we add half a unit to that offset,
		// since otherwise we'd be casting from the upper left corner of the
		// center tile, and not the center (again, feel free to try it out).

		Draw(x,y);
		if(Solid(x,y))break;
		// we first draw and then test whether a tile is solid, because otherwise
		// we'd be unable to see the solid tiles.
	}
}
