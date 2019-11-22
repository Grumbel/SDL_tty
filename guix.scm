;; Copyright (c) 2019 Ingo Ruhnke <grumbel@gmail.com>
;;
;; This software is provided 'as-is', without any express or implied
;; warranty. In no event will the authors be held liable for any
;; damages arising from the use of this software.
;;
;; Permission is granted to anyone to use this software for any
;; purpose, including commercial applications, and to alter it and
;; redistribute it freely, subject to the following restrictions:
;;
;;   1. The origin of this software must not be misrepresented; you
;;      must not claim that you wrote the original software. If you
;;      use this software in a product, an acknowledgment in the
;;      product documentation would be appreciated but is not
;;      required.
;;
;;   2. Altered source versions must be plainly marked as such, and
;;      must not be misrepresented as being the original software.
;;
;;   3. This notice may not be removed or altered from any source
;;      distribution.

(set! %load-path
      (cons* "/ipfs/QmetP3eCAM9q3VPCj9BvjFdWkTA7voycebnXjyfc2zacFE/guix-cocfree_v0.0.0-45-g0fe3c86"
             %load-path))

(use-modules (guix build-system cmake)
             ((guix licenses) #:prefix license:)
             (guix packages)
             (gnu packages pkg-config)
             (gnu packages sdl)
             (guix-cocfree utils))

(define %source-dir (dirname (current-filename)))

(define-public sdl-tty
  (package
   (name "sdl-tty")
   (version (version-from-source %source-dir))
   (source (source-from-source %source-dir))
   (build-system cmake-build-system)
   (arguments
    `(#:tests? #f)) ; no tests
   (native-inputs `(("pkg-config" ,pkg-config)))
   (inputs `(("sdl" ,sdl)
             ("sdl-image" ,sdl-image)))
   (synopsis "Terminal-like text output for SDL")
   (description "Terminal-like text output for SDL")
   (home-page "https://gitlab.com/grumbel/SDL_tty")
   (license license:zlib)))

sdl-tty

;; EOF ;;
