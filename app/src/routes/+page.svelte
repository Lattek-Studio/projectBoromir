<script>
	import { Tab } from '$ui'
	import { authStore } from '$lib/stores/auth'
	let uid;
	authStore.subscribe((curr) => {
		console.log('CURR', curr);
		uid = curr?.currentUser?.uid;
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
	<Tab />
</section>

<style>
	section{
		margin: 0 auto;
		width: fit-content;
	}
</style>
