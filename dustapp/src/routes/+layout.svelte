<script>
	import './styles.css'

    import { page } from '$app/stores'
    import { goto } from '$app/navigation';

    import { Capacitor } from "@capacitor/core";
	import { StatusBar, Style } from '@capacitor/status-bar';

    let path;
    $: path = $page.url.pathname;

   
  import { onMount } from 'svelte';

	onMount(async () => {
		if (Capacitor.isPluginAvailable('StatusBar') && Capacitor.getPlatform() !== 'web'){
			// StatusBar.setBackgroundColor({ color: '#071e22' });
            StatusBar.setStyle({ style: Style.Dark }),
            StatusBar.setBackgroundColor({
                color: "#071e22"
            })
            // StatusBar.hide()
		}
	});
</script>
<nav>
    <div class="nav">
        <div class="title" on:mousedown={()=>goto("/")}>
            <svg width="61" height="40" viewBox="0 0 61 40" fill="none" xmlns="http://www.w3.org/2000/svg">
                <path d="M3.57711 26.3514C3.57711 26.3514 -1.28289 14.3013 9.07711 11.7613C9.07711 11.7613 11.6172 2.67123 19.6472 6.90123C19.6472 6.90123 23.0271 -3.03867 31.2771 2.25133C31.2771 2.25133 39.7371 -4.51875 43.3271 5.42125C43.3271 5.42125 54.327 5.63127 50.727 17.6913C50.727 17.6913 55.167 20.0213 53.477 24.4613C53.477 24.4613 59.1871 23.6115 60.0371 30.3815C60.0371 30.3815 57.927 37.1513 48.197 33.9813C48.197 33.9813 41.547 40.1114 33.667 34.8314C33.667 34.8314 28.7471 40.3312 21.5571 34.4112C21.5571 34.4112 18.8072 40.5413 11.4072 38.4313C11.4072 38.4313 3.79714 41.6814 2.10714 33.8214C2.10714 33.8214 -1.70288 29.3415 3.58712 26.3815L3.57711 26.3514Z" fill="var(--accent)"/>
            </svg>                
            <a href="/">Dust</a>
        </div>
        <div class="{path=='/'?'active':''} item" on:mousedown={()=>goto("/")}>
            <img src="/dashboard.png" alt="dashboard"/>
            <a href="/">Dashboard</a>
        </div>
        <div class="{path=='/ranks'?'active':''} item" on:mousedown={()=>goto("/ranks")}>
            <img src="/ranks.png" alt="ranks"/>
            <a href="/ranks">Ranks</a>
        </div>
        <div class="{path=='/stats'?'active':''} item" on:mousedown={()=>goto("/stats")}>
            <img src="/stats.png" alt="stats"/>
            <a href="/stats">Stats</a>
        </div>
    </div>
    <div class="app">
        <div class="bar">
            <img class="settings" src="/settings.png" alt="logo"  on:mousedown={()=>goto("/settings")}/>
            <div class="title" on:mousedown={()=>goto("/")}>
                <svg height="30px" viewBox="0 0 61 40" fill="none" xmlns="http://www.w3.org/2000/svg" style="margin-right: 8px;">
                    <path d="M3.57711 26.3514C3.57711 26.3514 -1.28289 14.3013 9.07711 11.7613C9.07711 11.7613 11.6172 2.67123 19.6472 6.90123C19.6472 6.90123 23.0271 -3.03867 31.2771 2.25133C31.2771 2.25133 39.7371 -4.51875 43.3271 5.42125C43.3271 5.42125 54.327 5.63127 50.727 17.6913C50.727 17.6913 55.167 20.0213 53.477 24.4613C53.477 24.4613 59.1871 23.6115 60.0371 30.3815C60.0371 30.3815 57.927 37.1513 48.197 33.9813C48.197 33.9813 41.547 40.1114 33.667 34.8314C33.667 34.8314 28.7471 40.3312 21.5571 34.4112C21.5571 34.4112 18.8072 40.5413 11.4072 38.4313C11.4072 38.4313 3.79714 41.6814 2.10714 33.8214C2.10714 33.8214 -1.70288 29.3415 3.58712 26.3815L3.57711 26.3514Z" fill="var(--accent)"/>
                </svg> 
                <a href="/">Dust</a>
            </div>
            <img class="notifications" src="/notifications.png" alt="notifications" />
        </div>
        <div class="content">
            <slot />
        </div>
    </div>
</nav>
<style>
    nav{
        display:flex;
        /* grid-template-columns: clamp(200px, 15vw, 600px) auto; */
    }
    img{
        height: 1.5rem;
    }
    .nav{
        display:flex;
        flex-direction:column;
        border-right: 1px solid var(--gray);
        padding: 1rem 1.5rem;
        min-height: 100vh;
        max-height: 100vh;
    }
    .title{
        display:flex;
        align-items:center;
        place-content: center;
    }
    .item{
        display:flex;
        align-items:center;
        gap: 1rem;
        padding: 1rem 1.25rem;
        margin-bottom: 1rem;
        border-radius: 69rem;
        border: 1px solid transparent;
    }
    a{
        display: inline;
        text-decoration: none;
        color: inherit;
    }
    .title > a{
        font-size: 1.5rem;
        font-weight: bold;
    }
    .title{
        display: flex;
        margin-bottom: 4rem;
    }
    .nav > div:not(.title):not(.active){
        opacity: 0.5;
    }
    .active{
        /* border-bottom: 1px solid var(--accent); */
        opacity: 1;
        border: 1px solid var(--accent);
        background-color: var(--bgLight);
    }
    .content{
        padding: 1rem;
        max-height: calc(100vh - 4rem);
        overflow-y: auto;
    }
    .app{
        display:flex;
        width: 100%;
        flex-direction: column;
    }
    .bar{
        display: flex;
        justify-content: flex-end;
        align-items: center;
        padding: 1rem;
    }
    .bar > .title{
        display: none;
        margin-bottom: 0;
    }
    .bar > .settings{
        display: none;
    }
    .nav > *{
        transition: all 0.2s ease-in-out;
    }
    .nav > div:not(.title):hover{
        cursor: pointer;
        transform: scale(1.1);
        opacity: 1;
    }
    @media (max-width: 600px){
        nav{
            display: grid;
            grid-template-columns: 1fr;
            grid-template-rows: auto 9vh;
            height: 100vh;
        }
        .app{
            grid-column-start: 1;
            grid-column-end: 1;
        }
        .nav{
            min-height: 0;
            grid-row-start: 2;
            grid-row-end: 2;
            display: flex;
            flex-direction: row;
            justify-content: space-around;
            border-right: 0;
            border-top: 1px solid var(--gray);
        }
        .nav > div{
            margin-bottom: 0;
        }
        .title{
            display: none;
        }
        .bar{
            justify-content: space-between;
        }
        .bar > .title{
            display: flex;
        }
        .bar > .settings, .bar > .notifications{
            display: block;
        }
        .item:not(.active) > a{
            display: none;
        }
        .content{
        padding: 1rem;
        max-height: calc(100vh - 8rem);
        overflow-y: auto;
    }
    }
</style>