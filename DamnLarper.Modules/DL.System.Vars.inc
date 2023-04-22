// Module written by DEntisT, © & ® BRACE™.




new embed_titles[][256] = {
	"i can't even rest",
	"bruh why?",
	"LMAO man help pls",
	"c'mon",
	"i'm done",
	"dis cmd is really cool, isn't it?",
	"finally bro!"
};

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

new QuestionAnswers[][256] = {
	"sure, why not",
	"are you out of your mind?",
	"only if your mom is ok with it",
	"idk",
	"i am just a stupid ai.",
	"i don't think your dad would agree",
	"that's not ok.",
	"i am sure not",
	"ask your dad",
	"ask your mom later",
	"huh?",
	"shut up",
	"i don't like ur tone.",
	"LMAO",
	"LOL",
	"tell me you aren't that dumb.",
	"pls no",
	"what is that?",
	"i am sure that's okay.",
	"no",
	"yes",
	"i am a magician",
	"don't be so sure about that",
	"ask your dog",
	"smh",
	"ur annoying",
	"c'mon man",
	"obviously",
	"that's sus",
	"hmmmmmmm",
	"ok",
	"log off.",
	"i could not care less",
	"tbh that's stupid",
	"idk, try using `"BOT_PREFIX"search`",
	"when",
	"why",
	"how",
	"bruh"
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

new BotTips[][256] = {
	"You can turn these off with `"BOT_PREFIX"userconfig`."
};