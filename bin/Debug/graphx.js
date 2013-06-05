   paper.install(window);
var tool;
var ex;
window.onload = function(){
paper.setup(canvas);
var c =view.center;
project.currentStyle = {
	strokeColor: 'red'
};
//var path = new Path.Circle(new Point(100, 100), 50);
var pagex = new Path();
pagex.add([c.x+500,c.y]);
pagex.add([c.x-500,c.y]);
var pagey = new Path();
pagey.add([c.x,c.y+300]);
pagey.add([c.x,c.y-300]);
view.draw();
}
function draw(){

	 var c= view.center;
	 var x = c.x;
	 var y = c.y;
	 var cen = new Path.Circle(c,2).fillColor= 'red';
   ex = document.forms[0][0].value;
var graph = new Path();
for(var i=-500; i<=500;i++)
{var cx,cy;
	cx = x+i;
	cy = y+(25*f(i/50,ex));
	graph.add([cx,cy]);
	
}
graph.smooth();
graph.strokeColor = 'black';
view.draw();
}


function f(x,expr)
{var res = 0; var extemp = expr;var ind;var r;var cou=0;var start,end;var compute,subexp,subres;compute = false;

var l = extemp.length;
for( var i=0;i<l;i++)
{
	var ch = extemp.charAt(i);
	if(ch=='(')
	{
		cou++;
		if(cou==1)
		start = i+1;
	}
	else if(ch==')')
	{
		cou--;
		if(cou==0)
		{
			compute = true;
		end = i;
	}
	if(compute)
	{
		compute = false;
		subexp = extemp.substring(start,end);
		
		subres = Number(f(x,subexp))*-1;
		var r = '('+subexp+')';
		extemp = extemp.replace(r,String(subres));
	}
	
}
}
	while(extemp.indexOf('sin')!=-1)
	{ ind = extemp.indexOf('sin')+3;
		var nxt = getNext(extemp,ind);
				r= 'sin'+nxt;
		if(nxt=='x')
		var sx = String(Math.sin(x));
		else
		{
		nxt = Number(nxt);
		var sx = String(Math.sin(nxt));
		}
		extemp = extemp.replace(r,sx);	}
		
	while(extemp.indexOf('cos')!=-1)
	{ ind = extemp.indexOf('cos')+3;
		var nxt = getNext(extemp,ind);
				r= 'cos'+nxt;
		if(nxt=='x')
		var sx = String(Math.cos(x));
		else
		{
		nxt = Number(nxt);
		var sx = String(Math.cos(nxt));
		}
		extemp = extemp.replace(r,sx);	}
	while(extemp.indexOf('tan')!=-1)
	{ ind = extemp.indexOf('tan')+3;
		var nxt = getNext(extemp,ind);
				r= 'tan'+nxt;
		if(nxt=='x')
		var sx = String(Math.tan(x));
		else
		{
		nxt = Number(nxt);
		var sx = String(Math.tan(nxt));
		}
		extemp = extemp.replace(r,sx);	}
		
	while(extemp.indexOf('^')!=-1)
	{
		var i = extemp.indexOf('^');
		var b = getPrev(extemp,(i-1));
		var e = getNext(extemp,(i+1));
		var sr = String(b+'^'+e);
				if(b=='x')
		b=Number(x);
		else
		b = Number(b);
if(e=='x')
e = Number(x);
 else
 e = Number(e);
		var r = String(Math.pow(b,e));
	extemp = extemp.replace(sr,r);
		
	}
	res = -1*eval(extemp);
	return (res);
}

function getNext(expr,ind)
{var cont = true; var res = "";
	do
	{
		var c = expr.charAt(ind++);
		if(c=='x')
		{
			res= 'x';
			break;
		}
		else if(!isNaN(c)||c=='.'||c=='-')
			res=res+c;
			else
			cont=false;
	}
	while(cont&&ind<expr.length);
				return res;
}
function getPrev(expr,ind)
{var cont = true; var res = "";
	do
	{
		var c = expr.charAt(ind--);
		if(c=='x')
		{
			res= 'x';
			break;
		}
		else if(!isNaN(c)||c=='.'||c=='-')
			res=c+res;
			else
			cont=false;
	}
	while(cont&&ind>-1);
				return res;
}