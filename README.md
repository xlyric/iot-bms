# BMS (Battery Management System)

Ce projet est un système de gestion de batterie (BMS) pour une batterie Li-ion. Il utilise une carte de contrôle avec les fonctionnalités suivantes :

- **Afficheur OLED** : Pour afficher les informations de la batterie en temps réel.
- **Sonde Dallas** : Pour mesurer la température de la batterie.
- **Mesure de tension** : Pour surveiller la tension de la batterie.
- **MQTT** : Pour envoyer les données vers Home Assistant à terme.

## Fonctionnalités

- Surveillance de la tension de la batterie.
- Surveillance de la température de la batterie.
- Affichage des informations sur un écran OLED.
- Envoi des données vers Home Assistant via MQTT (à venir).

## Installation

1. Clonez ce dépôt.
2. Ouvrez le projet avec PlatformIO.
3. Compilez et téléversez le code sur votre carte de contrôle.

## Utilisation

Une fois le code téléversé, le système commencera à surveiller la batterie et à afficher les informations sur l'écran OLED. Les fonctionnalités MQTT seront ajoutées dans une future mise à jour.

## Contributions

Les contributions sont les bienvenues. Veuillez soumettre une pull request pour toute amélioration ou correction.

## Licence

Ce projet est sous licence MIT. Voir le fichier [LICENSE](LICENSE) pour plus de détails.

## TODO 

- Codage de la partie Web pour le reglage du pont diviseur, à voir si c'est vraiment utile