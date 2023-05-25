import{a as He,s as xe}from"../chunks/firebase.601ba531.js";import{w as Be}from"../chunks/index.912cec11.js";import{S as Re,i as We,s as Fe,C as Ke,k as m,a as U,q as ue,l as g,m as C,c as M,r as fe,h as E,D as Q,n as l,b as Je,E as i,F as ae,G as Ne,H as Qe,I as Xe,g as Ye,d as Ze,J as et,K as tt,o as st}from"../chunks/index.276b7e77.js";import{p as rt}from"../chunks/stores.aeafcd18.js";import{j as at}from"../chunks/singletons.ea3d55b7.js";const nt=Be({isLoading:!0,currentUser:null}),ot={login:async()=>{await xe(He)}};He.onAuthStateChanged(t=>{nt.update(e=>({...e,isLoading:!1,currentUser:t}))});ot.login();const lt=!0,kt=Object.freeze(Object.defineProperty({__proto__:null,prerender:lt},Symbol.toStringTag,{value:"Module"}));const ne=at("goto");/*! Capacitor: https://capacitorjs.com/ - MIT License */const it=t=>{const e=new Map;e.set("web",{name:"web"});const s=t.CapacitorPlatforms||{currentPlatform:{name:"web"},platforms:e},n=(o,c)=>{s.platforms.set(o,c)},r=o=>{s.platforms.has(o)&&(s.currentPlatform=s.platforms.get(o))};return s.addPlatform=n,s.setPlatform=r,s},ct=t=>t.CapacitorPlatforms=it(t),Ve=ct(typeof globalThis<"u"?globalThis:typeof self<"u"?self:typeof window<"u"?window:typeof global<"u"?global:{});Ve.addPlatform;Ve.setPlatform;var oe;(function(t){t.Unimplemented="UNIMPLEMENTED",t.Unavailable="UNAVAILABLE"})(oe||(oe={}));class Le extends Error{constructor(e,s,n){super(e),this.message=e,this.code=s,this.data=n}}const dt=t=>{var e,s;return t!=null&&t.androidBridge?"android":!((s=(e=t==null?void 0:t.webkit)===null||e===void 0?void 0:e.messageHandlers)===null||s===void 0)&&s.bridge?"ios":"web"},ut=t=>{var e,s,n,r,o;const c=t.CapacitorCustomPlatform||null,a=t.Capacitor||{},h=a.Plugins=a.Plugins||{},d=t.CapacitorPlatforms,_=()=>c!==null?c.name:dt(t),y=((e=d==null?void 0:d.currentPlatform)===null||e===void 0?void 0:e.getPlatform)||_,W=()=>y()!=="web",T=((s=d==null?void 0:d.currentPlatform)===null||s===void 0?void 0:s.isNativePlatform)||W,V=f=>{const v=Z.get(f);return!!(v!=null&&v.platforms.has(y())||Y(f))},ie=((n=d==null?void 0:d.currentPlatform)===null||n===void 0?void 0:n.isPluginAvailable)||V,X=f=>{var v;return(v=a.PluginHeaders)===null||v===void 0?void 0:v.find(G=>G.name===f)},Y=((r=d==null?void 0:d.currentPlatform)===null||r===void 0?void 0:r.getPluginHeader)||X,A=f=>t.console.error(f),q=(f,v,G)=>Promise.reject(`${G} does not have an implementation of "${v}".`),Z=new Map,ce=(f,v={})=>{const G=Z.get(f);if(G)return console.warn(`Capacitor plugin "${f}" already registered. Cannot register plugins twice.`),G.proxy;const p=y(),k=Y(f);let I;const de=async()=>(!I&&p in v?I=typeof v[p]=="function"?I=await v[p]():I=v[p]:c!==null&&!I&&"web"in v&&(I=typeof v.web=="function"?I=await v.web():I=v.web),I),B=(u,P)=>{var D,w;if(k){const L=k==null?void 0:k.methods.find(O=>P===O.name);if(L)return L.rtype==="promise"?O=>a.nativePromise(f,P.toString(),O):(O,F)=>a.nativeCallback(f,P.toString(),O,F);if(u)return(D=u[P])===null||D===void 0?void 0:D.bind(u)}else{if(u)return(w=u[P])===null||w===void 0?void 0:w.bind(u);throw new Le(`"${f}" plugin is not implemented on ${p}`,oe.Unimplemented)}},J=u=>{let P;const D=(...w)=>{const L=de().then(O=>{const F=B(O,u);if(F){const j=F(...w);return P=j==null?void 0:j.remove,j}else throw new Le(`"${f}.${u}()" is not implemented on ${p}`,oe.Unimplemented)});return u==="addListener"&&(L.remove=async()=>P()),L};return D.toString=()=>`${u.toString()}() { [capacitor code] }`,Object.defineProperty(D,"name",{value:u,writable:!1,configurable:!1}),D},N=J("addListener"),ee=J("removeListener"),H=(u,P)=>{const D=N({eventName:u},P),w=async()=>{const O=await D;ee({eventName:u,callbackId:O},P)},L=new Promise(O=>D.then(()=>O({remove:w})));return L.remove=async()=>{console.warn("Using addListener() without 'await' is deprecated."),await w()},L},$=new Proxy({},{get(u,P){switch(P){case"$$typeof":return;case"toJSON":return()=>({});case"addListener":return k?H:N;case"removeListener":return ee;default:return J(P)}}});return h[f]=$,Z.set(f,{name:f,proxy:$,platforms:new Set([...Object.keys(v),...k?[p]:[]])}),$},x=((o=d==null?void 0:d.currentPlatform)===null||o===void 0?void 0:o.registerPlugin)||ce;return a.convertFileSrc||(a.convertFileSrc=f=>f),a.getPlatform=y,a.handleError=A,a.isNativePlatform=T,a.isPluginAvailable=ie,a.pluginMethodNoop=q,a.registerPlugin=x,a.Exception=Le,a.DEBUG=!!a.DEBUG,a.isLoggingEnabled=!!a.isLoggingEnabled,a.platform=a.getPlatform(),a.isNative=a.isNativePlatform(),a},ft=t=>t.Capacitor=ut(t),le=ft(typeof globalThis<"u"?globalThis:typeof self<"u"?self:typeof window<"u"?window:typeof global<"u"?global:{}),ke=le.registerPlugin;le.Plugins;class qe{constructor(e){this.listeners={},this.windowListeners={},e&&(console.warn(`Capacitor WebPlugin "${e.name}" config object was deprecated in v3 and will be removed in v4.`),this.config=e)}addListener(e,s){this.listeners[e]||(this.listeners[e]=[]),this.listeners[e].push(s);const r=this.windowListeners[e];r&&!r.registered&&this.addWindowListener(r);const o=async()=>this.removeListener(e,s),c=Promise.resolve({remove:o});return Object.defineProperty(c,"remove",{value:async()=>{console.warn("Using addListener() without 'await' is deprecated."),await o()}}),c}async removeAllListeners(){this.listeners={};for(const e in this.windowListeners)this.removeWindowListener(this.windowListeners[e]);this.windowListeners={}}notifyListeners(e,s){const n=this.listeners[e];n&&n.forEach(r=>r(s))}hasListeners(e){return!!this.listeners[e].length}registerWindowListener(e,s){this.windowListeners[s]={registered:!1,windowEventName:e,pluginEventName:s,handler:n=>{this.notifyListeners(s,n)}}}unimplemented(e="not implemented"){return new le.Exception(e,oe.Unimplemented)}unavailable(e="not available"){return new le.Exception(e,oe.Unavailable)}async removeListener(e,s){const n=this.listeners[e];if(!n)return;const r=n.indexOf(s);this.listeners[e].splice(r,1),this.listeners[e].length||this.removeWindowListener(this.windowListeners[e])}addWindowListener(e){window.addEventListener(e.windowEventName,e.handler),e.registered=!0}removeWindowListener(e){e&&(window.removeEventListener(e.windowEventName,e.handler),e.registered=!1)}}const Ue=t=>encodeURIComponent(t).replace(/%(2[346B]|5E|60|7C)/g,decodeURIComponent).replace(/[()]/g,escape),Me=t=>t.replace(/(%[\dA-F]{2})+/gi,decodeURIComponent);class vt extends qe{async getCookies(){const e=document.cookie,s={};return e.split(";").forEach(n=>{if(n.length<=0)return;let[r,o]=n.replace(/=/,"CAP_COOKIE").split("CAP_COOKIE");r=Me(r).trim(),o=Me(o).trim(),s[r]=o}),s}async setCookie(e){try{const s=Ue(e.key),n=Ue(e.value),r=`; expires=${(e.expires||"").replace("expires=","")}`,o=(e.path||"/").replace("path=",""),c=e.url!=null&&e.url.length>0?`domain=${e.url}`:"";document.cookie=`${s}=${n||""}${r}; path=${o}; ${c};`}catch(s){return Promise.reject(s)}}async deleteCookie(e){try{document.cookie=`${e.key}=; Max-Age=0`}catch(s){return Promise.reject(s)}}async clearCookies(){try{const e=document.cookie.split(";")||[];for(const s of e)document.cookie=s.replace(/^ +/,"").replace(/=.*/,`=;expires=${new Date().toUTCString()};path=/`)}catch(e){return Promise.reject(e)}}async clearAllCookies(){try{await this.clearCookies()}catch(e){return Promise.reject(e)}}}ke("CapacitorCookies",{web:()=>new vt});const mt=async t=>new Promise((e,s)=>{const n=new FileReader;n.onload=()=>{const r=n.result;e(r.indexOf(",")>=0?r.split(",")[1]:r)},n.onerror=r=>s(r),n.readAsDataURL(t)}),gt=(t={})=>{const e=Object.keys(t);return Object.keys(t).map(r=>r.toLocaleLowerCase()).reduce((r,o,c)=>(r[o]=t[e[c]],r),{})},ht=(t,e=!0)=>t?Object.entries(t).reduce((n,r)=>{const[o,c]=r;let a,h;return Array.isArray(c)?(h="",c.forEach(d=>{a=e?encodeURIComponent(d):d,h+=`${o}=${a}&`}),h.slice(0,-1)):(a=e?encodeURIComponent(c):c,h=`${o}=${a}`),`${n}&${h}`},"").substr(1):null,pt=(t,e={})=>{const s=Object.assign({method:t.method||"GET",headers:t.headers},e),r=gt(t.headers)["content-type"]||"";if(typeof t.data=="string")s.body=t.data;else if(r.includes("application/x-www-form-urlencoded")){const o=new URLSearchParams;for(const[c,a]of Object.entries(t.data||{}))o.set(c,a);s.body=o.toString()}else if(r.includes("multipart/form-data")){const o=new FormData;if(t.data instanceof FormData)t.data.forEach((a,h)=>{o.append(h,a)});else for(const a of Object.keys(t.data))o.append(a,t.data[a]);s.body=o;const c=new Headers(s.headers);c.delete("content-type"),s.headers=c}else(r.includes("application/json")||typeof t.data=="object")&&(s.body=JSON.stringify(t.data));return s};class wt extends qe{async request(e){const s=pt(e,e.webFetchExtra),n=ht(e.params,e.shouldEncodeUrlParams),r=n?`${e.url}?${n}`:e.url,o=await fetch(r,s),c=o.headers.get("content-type")||"";let{responseType:a="text"}=o.ok?e:{};c.includes("application/json")&&(a="json");let h,d;switch(a){case"arraybuffer":case"blob":d=await o.blob(),h=await mt(d);break;case"json":h=await o.json();break;case"document":case"text":default:h=await o.text()}const _={};return o.headers.forEach((y,W)=>{_[W]=y}),{data:h,headers:_,status:o.status,url:o.url}}async get(e){return this.request(Object.assign(Object.assign({},e),{method:"GET"}))}async post(e){return this.request(Object.assign(Object.assign({},e),{method:"POST"}))}async put(e){return this.request(Object.assign(Object.assign({},e),{method:"PUT"}))}async patch(e){return this.request(Object.assign(Object.assign({},e),{method:"PATCH"}))}async delete(e){return this.request(Object.assign(Object.assign({},e),{method:"DELETE"}))}}ke("CapacitorHttp",{web:()=>new wt});var Ce;(function(t){t.Dark="DARK",t.Light="LIGHT",t.Default="DEFAULT"})(Ce||(Ce={}));var Te;(function(t){t.None="NONE",t.Slide="SLIDE",t.Fade="FADE"})(Te||(Te={}));const Ge=ke("StatusBar");function bt(t){let e,s,n,r,o,c,a,h,d,_,y,W,T,V,ie,X,Y,A,q,Z,ce,x,f,v,G,p,k,I,de,B,J,N,ee,H,$,u,P,D,w,L,O,F,j,be,_e,te,$e,Pe,se,R,ye,De;const Ee=t[3].default,z=Ke(Ee,t,t[2],null);return{c(){e=m("nav"),s=m("div"),n=m("div"),r=m("img"),c=U(),a=m("a"),h=ue("Dust"),d=U(),_=m("div"),y=m("img"),T=U(),V=m("a"),ie=ue("Dashboard"),Y=U(),A=m("div"),q=m("img"),ce=U(),x=m("a"),f=ue("Statistics"),G=U(),p=m("div"),k=m("img"),de=U(),B=m("a"),J=ue("Performance"),ee=U(),H=m("div"),$=m("div"),u=m("img"),D=U(),w=m("div"),L=m("img"),F=U(),j=m("a"),be=ue("Dust"),_e=U(),te=m("img"),Pe=U(),se=m("div"),z&&z.c(),this.h()},l(b){e=g(b,"NAV",{class:!0});var S=C(e);s=g(S,"DIV",{class:!0});var K=C(s);n=g(K,"DIV",{class:!0});var ve=C(n);r=g(ve,"IMG",{src:!0,alt:!0,class:!0}),c=M(ve),a=g(ve,"A",{href:!0,class:!0});var Oe=C(a);h=fe(Oe,"Dust"),Oe.forEach(E),ve.forEach(E),d=M(K),_=g(K,"DIV",{class:!0});var me=C(_);y=g(me,"IMG",{src:!0,alt:!0,class:!0}),T=M(me),V=g(me,"A",{href:!0,class:!0});var ze=C(V);ie=fe(ze,"Dashboard"),ze.forEach(E),me.forEach(E),Y=M(K),A=g(K,"DIV",{class:!0});var ge=C(A);q=g(ge,"IMG",{src:!0,alt:!0,class:!0}),ce=M(ge),x=g(ge,"A",{href:!0,class:!0});var Ae=C(x);f=fe(Ae,"Statistics"),Ae.forEach(E),ge.forEach(E),G=M(K),p=g(K,"DIV",{class:!0});var he=C(p);k=g(he,"IMG",{src:!0,alt:!0,class:!0}),de=M(he),B=g(he,"A",{href:!0,class:!0});var Ie=C(B);J=fe(Ie,"Performance"),Ie.forEach(E),he.forEach(E),K.forEach(E),ee=M(S),H=g(S,"DIV",{class:!0});var pe=C(H);$=g(pe,"DIV",{class:!0});var re=C($);u=g(re,"IMG",{class:!0,src:!0,alt:!0}),D=M(re),w=g(re,"DIV",{class:!0});var we=C(w);L=g(we,"IMG",{src:!0,class:!0}),F=M(we),j=g(we,"A",{href:!0,class:!0});var je=C(j);be=fe(je,"Dust"),je.forEach(E),we.forEach(E),_e=M(re),te=g(re,"IMG",{class:!0,src:!0}),re.forEach(E),Pe=M(pe),se=g(pe,"DIV",{class:!0});var Se=C(se);z&&z.l(Se),Se.forEach(E),pe.forEach(E),S.forEach(E),this.h()},h(){Q(r.src,o="/favicon.png")||l(r,"src",o),l(r,"alt","logo"),l(r,"class","svelte-17vlzcn"),l(a,"href","/"),l(a,"class","svelte-17vlzcn"),l(n,"class","title svelte-17vlzcn"),Q(y.src,W="/dashboard.png")||l(y,"src",W),l(y,"alt","dashboard"),l(y,"class","svelte-17vlzcn"),l(V,"href","/"),l(V,"class","svelte-17vlzcn"),l(_,"class",X=(t[0]=="/"?"active":"")+" item svelte-17vlzcn"),Q(q.src,Z="/statistics.png")||l(q,"src",Z),l(q,"alt","statistics"),l(q,"class","svelte-17vlzcn"),l(x,"href","/statistics"),l(x,"class","svelte-17vlzcn"),l(A,"class",v=(t[0]=="/statistics"?"active":"")+" item svelte-17vlzcn"),Q(k.src,I="/performance.png")||l(k,"src",I),l(k,"alt","performance"),l(k,"class","svelte-17vlzcn"),l(B,"href","/performance"),l(B,"class","svelte-17vlzcn"),l(p,"class",N=(t[0]=="/performance"?"active":"")+" item svelte-17vlzcn"),l(s,"class","nav svelte-17vlzcn"),l(u,"class","settings svelte-17vlzcn"),Q(u.src,P="/settings.png")||l(u,"src",P),l(u,"alt","logo"),Q(L.src,O="/favicon.png")||l(L,"src",O),l(L,"class","svelte-17vlzcn"),l(j,"href","/"),l(j,"class","svelte-17vlzcn"),l(w,"class","title svelte-17vlzcn"),l(te,"class","notifications svelte-17vlzcn"),Q(te.src,$e="/notifications.png")||l(te,"src",$e),l($,"class","bar svelte-17vlzcn"),l(se,"class","content svelte-17vlzcn"),l(H,"class","app svelte-17vlzcn"),l(e,"class","svelte-17vlzcn")},m(b,S){Je(b,e,S),i(e,s),i(s,n),i(n,r),i(n,c),i(n,a),i(a,h),i(s,d),i(s,_),i(_,y),i(_,T),i(_,V),i(V,ie),i(s,Y),i(s,A),i(A,q),i(A,ce),i(A,x),i(x,f),i(s,G),i(s,p),i(p,k),i(p,de),i(p,B),i(B,J),i(e,ee),i(e,H),i(H,$),i($,u),i($,D),i($,w),i(w,L),i(w,F),i(w,j),i(j,be),i($,_e),i($,te),i(H,Pe),i(H,se),z&&z.m(se,null),R=!0,ye||(De=[ae(n,"mousedown",t[4]),ae(_,"mousedown",t[5]),ae(A,"mousedown",t[6]),ae(p,"mousedown",t[7]),ae(u,"mousedown",t[8]),ae(w,"mousedown",t[9])],ye=!0)},p(b,[S]){(!R||S&1&&X!==(X=(b[0]=="/"?"active":"")+" item svelte-17vlzcn"))&&l(_,"class",X),(!R||S&1&&v!==(v=(b[0]=="/statistics"?"active":"")+" item svelte-17vlzcn"))&&l(A,"class",v),(!R||S&1&&N!==(N=(b[0]=="/performance"?"active":"")+" item svelte-17vlzcn"))&&l(p,"class",N),z&&z.p&&(!R||S&4)&&Ne(z,Ee,b,b[2],R?Xe(Ee,b[2],S,null):Qe(b[2]),null)},i(b){R||(Ye(z,b),R=!0)},o(b){Ze(z,b),R=!1},d(b){b&&E(e),z&&z.d(b),ye=!1,et(De)}}}function _t(t,e,s){let n;tt(t,rt,T=>s(1,n=T));let{$$slots:r={},$$scope:o}=e,c;st(async()=>{le.isPluginAvailable("StatusBar")&&le.getPlatform()!=="web"&&(Ge.setStyle({style:Ce.Dark}),Ge.setBackgroundColor({color:"#071e22"}))});const a=()=>ne("/"),h=()=>ne("/"),d=()=>ne("/statistics"),_=()=>ne("/performance"),y=()=>ne("/settings"),W=()=>ne("/");return t.$$set=T=>{"$$scope"in T&&s(2,o=T.$$scope)},t.$$.update=()=>{t.$$.dirty&2&&s(0,c=n.url.pathname)},[c,n,o,r,a,h,d,_,y,W]}class $t extends Re{constructor(e){super(),We(this,e,_t,bt,Fe,{})}}export{$t as component,kt as universal};
