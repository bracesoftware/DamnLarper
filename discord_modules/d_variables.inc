// Module written by DEntisT, © & ® BRACE™.

new DiplomyReplies[][256] = {
	"Did someone call my name?",
	"I heard my name!",
	"I'm here.",
	"I really can't help you now!",
	"Stop calling my name! Use commands...",
	"I'm just a bot - stop!",
	"Oh, hello!",
	"What's up?",
	"How are you sir?",
	"Be polite man!"
};

new DiplomyJokes[][512] = {
	"You.",
	"What's the best thing about Switzerland? I do not know, but the flag is a big plus.",
	"Why do we tell actors to “break a leg?” Because every play has a cast.",
	"I Googled \"how to start a wildfire\". I got 50k matches!",
	"What do you call someone wearing a belt with a watch attached to it? A waist of time.",
	"What do you call a man without a body and a nose? Nobody knows!",
	"What do you call a cute door? A-door-able!",
	"My ex-wife still misses me. But her aim is steadily improving!",
	"A horse walks into a bar. The bartender says, \"Why the long face?\"",
	"What do computers snack on? Microchips!",
	"Somebody stole all my lamps. I couldn't be more delighted!",
	"I broke my left arm and left leg. It is alright now!",
	"Three guys walk into a bar. They all said, ouch!",
	"What did the policeman say to his belly button? You're under a vest!",
	"You're becoming a vegetarian? I think that's a big missed steak!",
	"What does a dog say when he sits down on a piece of sandpaper? Ruff.",
	"An English teacher asked a student to name two pronouns. Student replied, \"Who, me?\"",
	"What do you call a rope made in European Union? Europe."
};

new dateupdated;

enum esettings
{
	log,
	gmc,
	eco,
	mod,
	cnt,
	ccmd,
	ac,
	rp
}

new settings[esettings];


new listpreview[4000];

new RISE_OF_NATIONS_GLOBALSTRING[1024];

new activity[100];