int viewrad=30;
for(int r=0;r<viewrad*2.5*M_PI+1;r++){
	float rf=(float)r/viewrad/2.5*2,dx=0,dy=0;

	switch((int)(rf*8/2/M_PI)){
		case 7:case 0:dx=-1,dy=sin(rf)/cos(rf);break;
		case 1:case 2:dx=cos(rf)/sin(rf),dy=+1;break;
		case 3:case 4:dx=+1,dy=sin(rf)/cos(rf);break;
		case 5:case 6:dx=cos(rf)/sin(rf),dy=-1;break;
	}

	for(int i=0;i<viewrad;i++){
		if(i*i*(dx*dx+dy*dy)>viewrad*viewrad)break;
		int x=i*dx+sx/2+.5,y=i*dy+sy/2+.5;
		Draw(x,y);
		if(Solid(x,y))break;
	}
}
