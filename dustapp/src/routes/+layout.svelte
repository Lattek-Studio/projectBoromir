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
            <img src="/favicon.png" alt="logo"/>
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
        <div class="{path=='/performance'?'active':''} item" on:mousedown={()=>goto("/performance")}>
            <img src="/performance.png" alt="performance"/>
            <a href="/performance">Performance</a>
        </div>
    </div>
    <div class="app">
        <div class="bar">
            <img class="settings" src="/settings.png" alt="logo"  on:mousedown={()=>goto("/settings")}/>
            <div class="title" on:mousedown={()=>goto("/")}>
                <img src="/favicon.png" />
                <a href="/">Dust</a>
            </div>
            <img class="notifications" src="/notifications.png" />
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
    }
</style>