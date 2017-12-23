# SmartVitrine
Nathan Hubens & Alexandre Beis


This is our project called SmartVitrine. The visual merchandising is a booming market. Companies are investing a lot of money to optimize their product and/or advertisements in order to make them as eye-catching as possible.

The goal is to simulate a shop window where one of the mannequin differs from the others by its color or posture. We then applied several methods to see if this mannequin was really attracting the attention. These methods were divided into two parts : the human-based methods and the computer-based methods.


## Human-based methods

### Motion Capture

* Qualisys

We used the Qualisys system on 10 people and show them 4 images of our "shop window". Each of these people had only a hat with 3 sensors, the goal was only to track their head orientation.


### Eye-tracking




## Computer-based methods

### Saliency maps


* Rare 2012 (http://tcts.fpms.ac.be/attention/index.php?categorie1/models&model=001)

* Local Contrast (http://tcts.fpms.ac.be/attention/index.php?categorie1/models&model=005)

* Global Rarity (http://tcts.fpms.ac.be/attention/index.php?categorie1/models&model=004)

Generally, these algorithms had difficulties to get the correct results on the images where the mannequin differs by its posture. To get better results, a preprocessing step was added, which is a Gaussian blurring in order to catch more spatial information for these images.

### Deep learning

* Deep Visual Attention Prediction (https://arxiv.org/pdf/1705.02544.pdf)



