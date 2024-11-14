function show_runtime(){window.setTimeout("show_runtime()",1000);X=new 
    Date("12/31/2021 22:00:00");
    Y=new Date();T=(Y.getTime()-X.getTime());M=24*60*60*1000;
    a=T/M;A=Math.floor(a);b=(a-A)*24;B=Math.floor(b);c=(b-B)*60;C=Math.floor((b-B)*60);D=Math.floor((c-C)*60);
    years = Math.floor(A / 365); 
    A = A % 365; 
    document.getElementById('runtime_span').innerHTML=`<span>本站已经运行: </span >`+years+`<span > 年 </span>`+A+`<span > 天 </span>`+B+`<span> 小时 </span>`+C+`<span> 分 </span>`+D+`<span> 秒 </span>`}



show_runtime();