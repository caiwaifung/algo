program p1099;

const
  trytimes=30; 
  faillim=5;   
  maxn=250;  maxm=maxn*maxn;
var
  g:array[1..maxn,1..maxn]of boolean;
  p,q:array[1..maxn]of longint;
  n:longint;
  
procedure swap(var a,b:longint);
var
  tmp:longint;
begin
  tmp:=a;a:=b;b:=tmp;
end;

procedure randindex;
var
  i,j:longint;
begin
  for i:=1 to n do
  begin
    j:=random(n)+1;
    swap(p[i],p[j]);
  end;
end;
procedure randindex2;
var
  i,j:longint;
begin
  for i:=1 to n do
  begin
    j:=random(n)+1;
    swap(q[i],q[j]);
  end;
end;

// init
procedure readdata;
var
  a,b:longint;
begin
  read(n);
  fillchar(g,sizeof(g),false);
  while not seekeof do
  begin
    read(a,b);
    g[a,b]:=true; g[b,a]:=true;
  end;
end;

// solve
var
  vis:array[1..maxn]of boolean;
  c:array[1..maxn]of longint;
  tot:longint;
  
function adjust(x:longint):boolean;
var
  i,k:longint;
begin
  if vis[x] then exit(false);
  vis[x]:=true;
  for k:=1 to n do
  begin
    i:=p[k];
    if (not vis[i])and g[x,i]and ((c[i]=0)or(adjust(c[i])))
      then begin
        c[x]:=i;c[i]:=x; exit(true);
      end;
  end;
  exit(false);
end;
  
procedure solve;
var
  i,j:longint;
begin
  fillchar(c,sizeof(c),0);
  tot:=0;
  for i:=1 to n do
    if c[q[i]]=0
      then begin
        for j:=1 to faillim do
        begin
          fillchar(vis,sizeof(vis),false);
          if adjust(q[i])
            then begin inc(tot);break end;
        end;
      end;
end;

// main
var
  bst:array[1..maxn]of longint;
  ans:longint;
procedure main;
var
  i,j,k,times:longint;
begin
  randomize;
  for i:=1 to n do p[i]:=i;
  for i:=1 to n do q[i]:=i;
  ans:=0;
  for times:=1 to trytimes do
  begin
    randindex; randindex2;
    solve;
    if tot>ans
      then begin
             ans:=tot;
             move(c,bst,sizeof(c));
           end;
  end;
  writeln(ans*2);
  for i:=1 to n do
    if bst[i]>i
      then writeln(i,' ',bst[i]);
end;

begin
  readdata;
  main;
end.

