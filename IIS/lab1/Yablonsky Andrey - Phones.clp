; создание шаблона
(deftemplate Phone
	(field name (type STRING) (default ?NONE))
	(field codeName (type STRING) (default "UNKNOWN"))
	(field developer (type STRING) (default ?NONE))
	(field os (type SYMBOL) (allowed-symbols Android iOS Windows) (default ?NONE))
	(field releaseYear (type INTEGER) (default ?NONE))
	(field ramSize (type INTEGER) (allowed-integers 1 2 4 6 8 10 12 16) (default ?NONE))
	(field sdSupport (type INTEGER) (allowed-integers 0 1) (default 0))
)

; добавлени неупорядоченных фактов
(deffacts Phones
	(Phone
		(name "iPhone X")
		(os iOS)
		(developer "Apple Inc.")
		(releaseYear 2018)
		(ramSize 6)
	)
	(Phone
		(name "Nexus 5")
		(codeName "Hammerhead")
		(os Android)
		(developer "LG")
		(releaseYear 2013)
		(ramSize 2)
		(sdSupport 0)
	)
	(Phone
		(name "Galaxy Nexus")
		(os Android)
		(developer "Samsung Electronics")
		(releaseYear 2011)
		(ramSize 1)
	)
	(Phone
		(name "Galaxy S10")
		(os Android)
		(developer "Samsung Electronics")
		(releaseYear 2019)
		(ramSize 12)
		(sdSupport 1)
	)
	(Phone
		(name "Nokia 1")
		(os Windows)
		(developer "Nocia Inc.")
		(releaseYear 2016)
		(ramSize 2)
		(sdSupport 1)
	)
)

; добавлени упорядоченных фактов
(deffacts PhoneInfo
	(The Nexus 2 was unveiled on October 31, 2013)
	(The Galaxy Nexus is a Android smartphone co-developed by Google and Samsung Electronics)
	(iPhone X was announced on September 12, 2017)
	(Samsung Galaxy S10 is a line of Android smartphones manufactured by Samsung Electronics)
)

; создает факты, объявленные через deffacts
(reset)

(facts)

