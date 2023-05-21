<script>
	import { Tab } from '$ui'
	import { authStore } from '$lib/stores/auth'
	import { dbStore } from '$lib/stores/db'
	import { Capacitor } from "@capacitor/core";
	import { StatusBar, Style } from '@capacitor/status-bar';
  import { onMount } from 'svelte';

	onMount(async () => {
		if (Capacitor.isPluginAvailable('StatusBar') && Capacitor.getPlatform() !== 'web'){
			StatusBar.setBackgroundColor({ color: '#3880ff' });
		}
	});
	let uid;
	authStore.subscribe((curr) => {
		console.log('CURR', curr);
		uid = curr?.currentUser?.uid;
	});
	let data
	dbStore.subscribe((curr) => {
		console.log('CURR', curr);
		data = curr;
	});
	
</script>

<svelte:head>
	<title>Home</title>
	<meta name="description" content="Svelte demo app" />
</svelte:head>

<section>
	<h1>Welcome to projectBoromir</h1>

	<p>This project is on its way to beeing finished...</p>
	<p>...but it's not there yet.</p>

	<p>Your user id is <span>{uid}</span></p>
	//loop through all keeys of data
	{#each Object.keys(data) as key}
		<p>The <span>{key}</span> emission of the world is <span>{data[key]}</span></p>
	{/each}
	<Tab />
	<a href="/app">Go to app</a>
</section>

<style>
	section{
		margin: 0 auto;
		width: fit-content;
	}
</style>
