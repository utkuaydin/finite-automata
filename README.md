# Regular Expression Engine

Final project for Formal Languages and Automata Theory (CMP3004) course.

## Execution

```
RegexEngine <expression> <filename>
```

## Sample Outputs
```
The following NFA was built:
Initial State: 
0
All States: 
[0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19]
Accepted States: 
[19]
Transitions: 
(0, 1, 'I')
(2, 3, 'n')
(1, 2, epsilon)
(4, 5, 'q')
(3, 4, epsilon)
(6, 7, 'u')
(5, 6, epsilon)
(8, 9, 'i')
(7, 8, epsilon)
(10, 11, 's')
(9, 10, epsilon)
(12, 13, 'i')
(11, 12, epsilon)
(14, 15, 't')
(13, 14, epsilon)
(16, 17, 'o')
(15, 16, epsilon)
(18, 19, 'r')
(17, 18, epsilon)
Accepted, line 94:       Chapter V. The Grand Inquisitor
Accepted, line 11045: “My poem is called ‘The Grand Inquisitor’; it’s a ridiculous thing, but I
Accepted, line 11050: Chapter V. The Grand Inquisitor
Accepted, line 11143: Dei_, been burnt by the cardinal, the Grand Inquisitor, in a magnificent
Accepted, line 11176: cardinal himself, the Grand Inquisitor, passes by the cathedral. He is an
Accepted, line 11191: Inquisitor. He blesses the people in silence and passes on. The guards
Accepted, line 11196: the prison is suddenly opened and the Grand Inquisitor himself comes in
Accepted, line 11637: it’s false—those are the worst of the Catholics, the Inquisitors, the
Accepted, line 11639: Inquisitor. What are these sins of mankind they take on themselves? Who
Accepted, line 11649: believe in God perhaps. Your suffering Inquisitor is a mere fantasy.”
Accepted, line 11662: why your Jesuits and Inquisitors have united simply for vile material
Accepted, line 11666: only one like my old Inquisitor, who had himself eaten roots in the desert
Accepted, line 11680: Perhaps nothing but Atheism, that’s all their secret. Your Inquisitor does
Accepted, line 11721: “I meant to end it like this. When the Inquisitor ceased speaking he
Accepted, line 30362: author of a promising poem entitled _The Grand Inquisitor_. I was only
Accepted, line 30365: “I forbid you to speak of _The Grand Inquisitor_,” cried Ivan, crimson
```
---
```
The following NFA was built:
Initial State: 
4
All States: 
[4, 0, 1, 2, 3, 5, 6, 7, 8, 9, 10, 11, 12, 21, 13, 14, 15, 16, 17, 18, 19, 20]
Accepted States: 
[16, 20]
Transitions: 
(4, 0, epsilon)
(4, 2, epsilon)
(0, 1, 'A')
(2, 3, 'a')
(5, 6, 'r')
(1, 5, epsilon)
(3, 5, epsilon)
(7, 8, 'r')
(6, 7, epsilon)
(9, 10, 'i')
(8, 9, epsilon)
(11, 12, 'v')
(10, 11, epsilon)
(21, 13, epsilon)
(21, 17, epsilon)
(13, 14, 'a')
(15, 16, 'l')
(14, 15, epsilon)
(17, 18, 'e')
(19, 20, 'd')
(18, 19, epsilon)
(12, 21, epsilon)
Accepted, line 780: they gave him, saying that he intended to go third class. On his arrival
Accepted, line 800: returned to our town only three years before Alyosha’s arrival. His former
Accepted, line 815: Pavlovitch might have got into terrible scrapes. Alyosha’s arrival seemed
Accepted, line 1155: The arrival of his two brothers, whom he had not known till then, seemed
Accepted, line 1157: his half‐brother Dmitri (though he arrived later) than with his own
Accepted, line 1253: Our visitors did not take part in the service, but arrived just as it was
Accepted, line 1289: It was strange that their arrival did not seem expected, and that they
Accepted, line 1393: “Here’s the hermitage. We’ve arrived,” cried Fyodor Pavlovitch. “The gates
Accepted, line 1768: awaiting me who arrived before you. But don’t you tell lies all the same,”
Accepted, line 3599: when Miüsov, Kalganov, and Ivan arrived. The other guest, Maximov, stood a
Accepted, line 3986: Alyosha’s arrival. Alyosha “pierced his heart” by “living with him, seeing
Accepted, line 4045: visitors had arrived, including Fyodor Pavlovitch, who was to stand god‐
Accepted, line 4714: whole town, gave suppers and dances. At the time I arrived and joined the
Accepted, line 4755: And then the commander of the division arrived, and kicked up the devil of
Accepted, line 4792: “Suddenly the new major arrived to take command of the battalion. The old
Accepted, line 5016: “Yes, formally and solemnly betrothed. It was all done on my arrival in
Accepted, line 5517: end of dinner, and since Ivan’s arrival in our town he had done so every
Accepted, line 6396: his arrival. Possibly he had been noticed from the window. At least,
Accepted, line 6400: Alyosha thought it strange that his arrival should cause such excitement.
Accepted, line 6518: heard long ago that the money had not arrived. He hadn’t sent the money,
Accepted, line 7239: arrived from town with a singular letter for him from Madame Hohlakov. In
Accepted, line 11878: At last, feeling very cross and ill‐humored, Ivan arrived home, and
Accepted, line 12560: evening, Fyodor Pavlovitch sent for Doctor Herzenstube, who arrived at
Accepted, line 12608: before Alyosha’s arrival; his visitors had gathered together in his cell
Accepted, line 14785: pointed out to all visitors on their arrival with peculiar respect and
Accepted, line 16403: a fatal influence in Grushenka’s life, and whose arrival she was expecting
Accepted, line 16414: in his speedy arrival. Moreover, in the “officer’s” first letter which had
Accepted, line 16581: When he was informed of the arrival of the “captain,” he at once refused
Accepted, line 17088: discussion Mitya got into the trap. Three hours later they arrived. At
Accepted, line 17103: At last they arrived, and Mitya at once ran to Grushenka.
Accepted, line 17892: arrival of this new man, and he had never thought of him! But how could
Accepted, line 18328: waiting for Mitya’s arrival to nail it down and put it in the cart. Pyotr
Accepted, line 18817: peeped out from the steps curious to see who had arrived.
Accepted, line 19169: looked at him very affectionately: before Mitya’s arrival, she had been
Accepted, line 19483: likely be here soon; but the cart with the provisions had not yet arrived.
Accepted, line 19485: but only three girls had arrived, and Marya was not there yet. And he did
Accepted, line 19852: expected cart had arrived with the wines and provisions.
Accepted, line 20945: arrived only five minutes before Pyotr Ilyitch, so that his story came,
Accepted, line 20999: the rural police, Mavriky Mavrikyevitch Schmertsov, who had arrived in the
Accepted, line 21002: “criminal” till the arrival of the proper authorities, to procure also
Accepted, line 21157: first arrival, Mitya had been made very welcome at the police captain’s,
Accepted, line 21414: arrived among us, had from the first felt marked respect for Ippolit
Accepted, line 22192: have done since you arrived?”
Accepted, line 23207: told him, as soon as he arrived, that he had brought three thousand with
Accepted, line 23256: they had not slept all night, and on the arrival of the police officers
Accepted, line 26193: with her. He arrived with her in rain and sleet, sat down on the sofa,
Accepted, line 26197: hour after her arrival. Suddenly she chanced to look at him intently: he
Accepted, line 26454: the first directly he arrived. He galloped here from Moscow at once, of
Accepted, line 26562: Hohlakov heard of his arrival from some one, and immediately sent to beg
Accepted, line 28164: on the first day of his arrival, then he had visited him once more, a
Accepted, line 28174: on Ivan’s going to see them as soon as he arrived in Moscow. But he did
Accepted, line 28175: not go to them till four days after his arrival. When he got the telegram,
Accepted, line 28191: brother. Yet he went to see Mitya on the first day of his arrival, and
Accepted, line 28264: “I only arrived to‐day.... To see the mess you are in here.” Smerdyakov
Accepted, line 30171: “Well, well, what happened when he arrived?”
Accepted, line 30569: drive him away: he disappeared when you arrived. I love your face,
Accepted, line 30722: Visitors had arrived not only from the chief town of our province, but
Accepted, line 30837: At ten o’clock the three judges arrived—the President, one honorary
Accepted, line 31381: advantage of his arrival, and rushed to consult him regardless of expense.
Accepted, line 31546: I have just arrived and have come to thank you for that pound of nuts, for
Accepted, line 34468: with when he arrived here, at his father’s house, and why depict my client
Accepted, line 35774: they all arrived together. Snegiryov opened the door hurriedly and called
```
